#!/bin/bash

# Configuration
# ---------------------------------------------------------------------

# The repository to clone as upstream (NO SPACES)
readonly REPO=COMP201-2014
# Default domain for school email
readonly SCHOOL=wit.edu
# The instructor's Github username
readonly INSTRUCTOR_GITHUB=lawrancej
# The instructor's Gitlab username
readonly INSTRUCTOR_GITLAB=lawrancej

# Runtime flags (DO NOT CHANGE)
# ---------------------------------------------------------------------
readonly PROGNAME=$(basename $0)
readonly ARGS="$@"
export TOP_PID=$$

# Utilities
# ---------------------------------------------------------------------

# Print out the size of the file
utility::fileSize() {
    local file="$1"
    local theSize="$(wc -c "$file" | awk '{print $1}' )"
    if [[ -z "$theSize" ]]; then
        theSize="0"
    fi
    printf "$theSize"
}

# "return" failure
utility::fail() {
    echo -n
    return 1
}

# "return" success
utility::success() {
    printf true
    return 0
}

# Return whether the last command was successful
utility::lastSuccess() {
    if [[ $? -eq 0 ]]; then
        utility::success
    else
        utility::fail
    fi
}

PIPES=""

pipe::rm() {
    rm -f $PIPES 2> /dev/null
}

app::shutdown() {
    echo
    printf "Cleaning up temporary files..." >&2
    pushd ~ > /dev/null
    pipe::rm
    rm -f temp.html 2> /dev/null
    popd > /dev/null
    echo -e "                                           [\e[1;32mDONE\e[0m]" >&2
    
    kill -9 $TOP_PID  2> /dev/null > /dev/null
}

trap app::shutdown EXIT
trap app::shutdown TERM

# Make a named pipe. It sniffs for mkfifo and mknod first.
# If we don't get a real pipe, just fake it with a regular file.
pipe::new() {
    local pipe="$1"
    rm -f "$pipe" 2> /dev/null
    # Attempt to make a pipe
    if [[ -n "$(which mkfifo)" ]]; then
        mkfifo "$pipe" 2> /dev/null
    elif [[ -n "$(which mknod)" ]]; then
        mknod "$pipe" p 2> /dev/null
    fi
    # If nothing's there, just fake it with regular files
    if [[ ! -p "$pipe" ]]; then
        touch "$pipe"
    fi
    PIPES="$PIPES $pipe"
}

# Wait until we get the pipe
pipe::await() {
    local pipe="$1"
    until [[ -p "$pipe" ]] || [[ -f "$pipe" ]]; do
        sleep 1
    done
}

# Cross-platform read from named pipe
pipe::write() {
    local pipe="$1"; shift
    local data="$1"
    # We use echo here so we can send multi-line strings on one line
    echo "$data" > "$pipe"
    # If we got a real pipe, the pipe will wait, but if we got a fake pipe, ...
    if [[ ! -p "$pipe" ]]; then
        # We need to wait for the other side to read
        while [[ -s "$pipe" ]]; do
            sleep 1
        done
    fi
}

# Cross-platform read from named pipe
pipe::read() {
    local pipe="$1"
    local line=""
    # If we got a real pipe, read will block until data comes in
    if [[ -p "$pipe" ]]; then
        # Hooray for blocking reads
        read -r line < "$pipe"
        echo -e "$line"
    # Windows users can't have nice things, as usual...
    elif [[ -f "$pipe" ]]; then
        # Wait for the other side to write
        while [[ ! -s "$pipe" ]]; do
            sleep 1
        done
        read -r line < "$pipe"
        # Remove the line that we just read, because we've got to fake it
        sed -i -e "1d" "$pipe"
        echo -e "$line"
    fi
}

# Get the MIME type by the extension
utility::MIMEType() {
    local fileName="$1";
    case $fileName in
        *.html | *.htm ) printf "text/html" ;;
        *.ico ) printf "image/x-icon" ;;
        *.css ) printf "text/css" ;;
        *.js ) printf "text/javascript" ;;
        *.txt ) printf "text/plain" ;;
        *.jpg ) printf "image/jpeg" ;;
        *.png ) printf "image/png" ;;
        *.svg ) printf "image/svg+xml" ;;
        *.pdf ) printf "application/pdf" ;;
        *.json ) printf "application/json" ;;
        * ) printf "application/octet-stream" ;;
    esac
}

# Cross-platform paste to clipboard
utility::paste() {
    case $OSTYPE in
        msys | cygwin ) echo "$1" > /dev/clipboard ;;
        linux* | bsd* ) echo "$1" | xclip -selection clipboard ;;
        darwin* ) echo "$1" | pbcopy ;;
        *) return 1 ;;
    esac
}

# Cross-platform file open
utility::fileOpen() {
    case $OSTYPE in
        msys | cygwin ) start "$1" ;;
        linux* | bsd* ) xdg-open "$1" ;;
        darwin* ) open "$1" ;;
        *) return 1 ;;
    esac
}

# Validate nonempty value matches a regex
# Return success if the value is not empty and matches regex, fail otherwise
utility::nonEmptyValueMatchesRegex() {
    local value="$1"; shift
    local regex="$1"
    
    # First, check if value is empty
    if [[ -z "$value" ]]; then
        utility::fail
    # Then, check whether value matches regex
    elif [[ -z "$(echo "$value" | grep -E "$regex" )" ]]; then
        utility::fail
    else
        utility::success
    fi
}

# SSH
# ---------------------------------------------------------------------

# Configure our keypair and add known hosts keys
ssh::configure() {
    # Just in case they've never used SSH before...
    mkdir -p ~/.ssh
    touch ~/.ssh/known_hosts
    
    # If our public/private keypair doesn't exist, make it.
    if ! [[ -f ~/.ssh/id_rsa.pub ]]; then
        # Use default location, set no phassphrase, no questions asked
        printf "\n" | ssh-keygen -t rsa -N '' 2> /dev/null > /dev/null
    fi
    
    # Add known hosts (i.e., bitbucket.org, github.com, gitlab.com)
    ssh-keyscan -t rsa bitbucket.org github.com gitlab.com ssh.github.com \
    altssh.bitbucket.org 2>&1 | sort -u - ~/.ssh/known_hosts | uniq > ~/.ssh/tmp_hosts
    cat ~/.ssh/tmp_hosts >> ~/.ssh/known_hosts
}

# Get the user's public key
ssh::getPublicKey() {
    cat ~/.ssh/id_rsa.pub | sed s/==.*$/==/ # Ignore the trailing comment
}

ssh::getPublicKeyForSed() {
    ssh::getPublicKey | sed -e 's/[/]/\\\//g'
}

# Test connection
ssh::connected() {
    local hostDomain="$1"; shift
    local sshTest=$(ssh -oStrictHostKeyChecking=no git@$hostDomain 2>&1)
    if [[ 255 -eq $? ]]; then
        utility::fail
    else
        utility::success
    fi
}

# User functions
# ---------------------------------------------------------------------

# Get the user's username
username::get() {
    local username="$USERNAME"
    if [[ -z "$username" ]]; then
        username="$(id -nu 2> /dev/null)"
    fi
    if [[ -z "$username" ]]; then
        username="$(whoami 2> /dev/null)"
    fi
    printf "$username"
}

# A full name needs a first and last name
full_name::valid() {
    local fullName="$1"
    utility::nonEmptyValueMatchesRegex "$fullName" "\w+ \w+"
}

# Set the full name
full_name::set() {
    local fullName="$1"
    if [[ $(full_name::valid "$fullName") ]]; then
        git config --global user.name "$fullName" > /dev/null
    fi
}

# Get the user's full name (Firstname Lastname); defaults to OS-supplied full name
# Side effect: set ~/.gitconfig user.name if unset and full name from OS validates.
full_name::get() {
    # First, look in the git configuration
    local fullName="$(git config --global user.name)"
    
    # Ask the OS for the user's full name, if it's not valid
    if [[ ! $(full_name::valid "$fullName") ]]; then
        local username="$(username::get)"
        case $OSTYPE in
            msys | cygwin )
                cat << 'EOF' > getfullname.ps1
$MethodDefinition = @'
[DllImport("secur32.dll", CharSet=CharSet.Auto, SetLastError=true)]
public static extern int GetUserNameEx (int nameFormat, System.Text.StringBuilder userName, ref uint userNameSize);
'@
$windows = Add-Type -MemberDefinition $MethodDefinition -Name 'Secur32' -Namespace 'Win32' -PassThru
$sb = New-Object System.Text.StringBuilder
$num=[uint32]256
$windows::GetUserNameEx(3, $sb, [ref]$num) | out-null
$sb.ToString()
EOF
                fullName=$(powershell -executionpolicy remotesigned -File getfullname.ps1 | sed -e 's/\(.*\), \(.*\)/\2 \1/')
                if [[ "$fullName" == "The argument 'getfullname.ps1' to the -File parameter does not exist. Provide the path to an existing '.ps1' file as an argument to the -File parameter." ]]; then
                    fullName=""
                fi
                rm getfullname.ps1 > /dev/null
                ;;
            linux* )
                fullName=$(getent passwd "$username" | cut -d ':' -f 5 | cut -d ',' -f 1)
                ;;
            darwin* )
                fullName=$(dscl . read /Users/`whoami` RealName | grep -v RealName | cut -c 2-)
                ;;
            *) fullName="" ;;
        esac
        
        # If we got a legit full name from the OS, update the git configuration to reflect it.
        full_name::set "$fullName"
    fi
    printf "$fullName"
}

# We're assuming that students have a .edu email address
email::valid() {
    local email="$(printf "$1" | tr '[:upper:]' '[:lower:]' | tr -d ' ')"
    utility::nonEmptyValueMatchesRegex "$email" "edu$"
}

# Get the user's email; defaults to username@school
# Side effect: set ~/.gitconfig user.email if unset
email::get() {
    # Try to see if the user already stored the email address
    local email="$(git config --global user.email | tr '[:upper:]' '[:lower:]' | tr -d ' ')"
    # If the stored email is bogus, ...
    if [[ ! $(email::valid "$email") ]]; then
        # Guess an email address and save it
        email="$(username::get)@$SCHOOL"
    fi
    # Resave, just in case of goofups
    git config --global user.email "$email"
    printf "$email"
}

# Set email for the user
email::set() {
    local email="$1"
    if [[ $(email::valid "$email") ]]; then
        git config --global user.email "$email" > /dev/null
    fi
}

# Generic project host configuration functions
# ---------------------------------------------------------------------

# Get the project host username; defaults to machine username
host_login::get() {
    local host="$1"
    local username="$(git config --global $host.login)"
    if [[ -z "$username" ]]; then
        username="$(username::get)"
    fi
    printf "$username"
}

# Set host login
host_login::set() {
    local host="$1"; shift
    local login="$1"
    if [[ $(host_login::valid "$login") ]]; then
        git config --global github.login "$login" > /dev/null
    fi
}

# A valid host login
host_login::valid() {
    local username="$1"
    # If the name is legit, ...
    utility::nonEmptyValueMatchesRegex "$username" "^[0-9a-zA-Z][0-9a-zA-Z-]*$"
}

# Git
# ---------------------------------------------------------------------

cloned=false

# Clone/fetch upstream
git::clone_upstream() {
    local host="$1"; shift
    local upstream="$1"
    pushd ~ > /dev/null
    if [[ ! -d $REPO ]]; then
        git clone "https://$host/$upstream/$REPO.git" 2> /dev/null > /dev/null
        if [[ $? -eq 0 ]]; then
            cloned=true
        fi
    fi
    
    pushd $REPO > /dev/null
    git submodule update --init --recursive > /dev/null
    git fetch --all 2> /dev/null > /dev/null
    if [[ $? -eq 0 ]]; then
        cloned=true
    fi
    popd > /dev/null
    
    utility::fileOpen $REPO
    popd > /dev/null
}

# Configure remotes
git::configure_remotes() {
    local hostDomain="$1"; shift
    local originLogin="$1"; shift
    local upstreamLogin="$1";
    local origin="git@$hostDomain:$originLogin/$REPO.git"
    local upstream="https://$hostDomain/$upstreamLogin/$REPO.git"
    
    # Configure remotes
    cd ~/$REPO
    git remote rm origin 2> /dev/null
    git remote rm upstream 2> /dev/null
    git remote add origin "$origin"
    git remote add upstream "$upstream"
    git config branch.master.remote origin
    git config branch.master.merge refs/heads/master
    git remote | tr '\n' ' '
}

# Push repository, and show the user local/remote repositories
# Preconditions:
# 1. SSH public/private keypair was generated
# 2. The project host username was properly set
# 3. SSH public key was shared with host
# 4. SSH is working
# 5. SSH key is in known_hosts
# 6. The private repo exists
git::push() {
    cd ~/$REPO
    git push -u origin master
}

# Is this a request line?
request::line() {
    local line="$1"
    if [[ -z "$(echo "$line" | grep -E "^GET|^HEAD|^POST|^PUT|^DELETE|^CONNECT|^OPTIONS|^TRACE")" ]]; then
        utility::fail
    fi
    utility::success
}

# Get the target (URL) of the request
request::target() {
    local request="$1"
    echo "$request" | sed -e 's/^[^ ]* \(.*\) HTTP\/.*/\1/' | head -n 1
}

# Get the file from the request target URL
request::file() {
    local request="$1"
    local target="$(request::target "$request")"
    # Leave the root request alone
    if [[ "$target" == "/" ]]; then
        printf "/"
    # Remove attempts to look outside the current folder, strip off the leading slash and the query
    else
        printf "$target" | sed -e 's/[.][.]//g' -e 's/^[/]*//g' -e 's/[?].*$//'
    fi
}

# Parse the request payload as form-urlencoded data
request::post_form_data() {
    local request="$1"
    local payload="$(request::payload "$request")"
    if [[ "$(request::lookup "$request" "Content-Type")" == "application/x-www-form-urlencoded" ]]; then
        echo "$payload" | tr '&' '\n'
    fi
}

# Return the key corresponding to the field
parameter::key() {
    local parameter="$1"
    echo "$parameter" | cut -d '=' -f 1
}

# Return the URL decoded value corresponding to the field
parameter::value() {
    local parameter="$1"
    echo -e "$(echo "$parameter" | cut -d '=' -f 2 | sed 'y/+/ /; s/%/\\x/g')"
}

# Given a header key, return the value
request::lookup() {
    local request="$1"; shift
    local key="$1"
    echo -e "$request" | grep "$key" | sed -e "s/^$key: \(.*\)/\1/"
}

# Return the payload of the request, if any (e.g., for POST requests)
request::payload() {
    local payload="$(echo "$1" | sed -e 's/^.*\\r\\n\\r\\n//')"
    echo -e "$payload"
}

# Pipe HTTP request into a string
request::new() {
    local line="$1"
    # If we got a request, ...
    if [[ $(request::line "$line") ]]; then
        local request="$line"
        # Read all headers
        while read -r header; do
            request="$request\n$header"
            if [[ -z "$header" ]]; then
                break
            fi
        done
        # Sometimes, we have a payload in the request, so handle that, too...
        local length="$(request::lookup "$request" "Content-Length")"
        local payload=""
        if [[ -n "$length" ]] && [[ "$length" != "0" ]]; then
            read -r -n "$length" payload
            request="$request\n$payload"
        fi
    fi
    # Return single line string
    echo "$request"
}

# Build a new response
response::new() {
    local status="$1"
    echo "HTTP/1.1 $status\r\nDate: $(date '+%a, %d %b %Y %T %Z')\r\nServer: Starter Upper"
}

# Add a header to the response
response::add_header() {
    local response="$1"; shift
    local header="$1";
    echo "$response\r\n$header"
}

# Add headers to response assuming file is payload
response::add_file_headers() {
    local response="$1"; shift
    local file="$1"
    response="$response\r\nContent-Length: $(utility::fileSize "$file")"
    response="$response\r\nContent-Encoding: binary"
    response="$response\r\nContent-Type: $(utility::MIMEType $file)"
    echo "$response"
}

# Add headers to response assuming string is payload
response::add_string_headers() {
    local response="$1"; shift
    local str="$1"; shift
    local type="$1"
    response="$response\r\nContent-Length: ${#str}"
    response="$response\r\nContent-Type: $type"
    echo "$response"
}

# "Send" the response headers
response::send() {
    echo -ne "$1\r\n\r\n"
}

# Send file with HTTP response headers
server::send_file() {
    local file="$1";
    if [[ -z "$file" ]]; then
        return 0
    fi
    local response="$(response::new "200 OK")"
    if [[ ! -f "$file" ]]; then
        response="$(response::new "404 Not Found")"
        file="404.html"
    fi
    response="$(response::add_file_headers "$response" "$file")"
    response::send "$response"
    cat "$file"
    echo "SENT $file" >&2
}

# Send string with HTTP response headers
server::send_string() {
    local str="$1"; shift
    local type="$1"; shift
    local response="$(response::new "200 OK")"
    response="$(response::add_string_headers "$response" "$str" "$(utility::MIMEType $type)")"
    response="$response\r\nAccess-Control-Allow-Origin: *"
    response::send "$response"
    echo "$str"
}

# Listen for requests
server::listen() {
    local request=""
    while read -r line; do
        request=$(request::new "$line")
        # Send the request through 
        pipe::write "$PIPE" "$request\n"
    done
}

# Respond to requests, using supplied route function
# The route function is a command that takes a request argument: it should send a response
server::respond() {
    local routeFunction="$1"
    local request=""
    pipe::await "$PIPE"
    while true; do
        request="$(pipe::read "$PIPE")"
        # Pass the request to the route function
        "$routeFunction" "$request"
    done
}

server::get_netcat() {
    local netcat=""
    # Look for netcat
    for program in "nc" "ncat" "netcat"; do
        if [[ -n "$(which $program)" ]]; then
            netcat=$program
            break
        fi
    done
    # Get netcat, if it's not already installed
    if [[ -z "$netcat" ]]; then
        curl http://nmap.org/dist/ncat-portable-5.59BETA1.zip 2> /dev/null > ncat.zip
        unzip -p ncat.zip ncat-portable-5.59BETA1/ncat.exe > nc.exe
        netcat="nc"
        rm ncat.zip
    fi
    printf $netcat
}

readonly PIPE=.httpipe

# Start the web server, using the supplied routing function
server::start() {
    local routes="$1"
    pipe::new "$PIPE"
    local nc=$(server::get_netcat)
    
    server::respond "$routes" | "$nc" -k -l 8080 | server::listen
}

# Determine if SSH connection works
github::connected() {
    # Test SSH connection on default port (22)
    if [[ ! $(ssh::connected "github.com") ]]; then
        printf "Host github.com\n  Hostname ssh.github.com\n  Port 443\n" >> ~/.ssh/config
        # Test SSH connection on port 443
        if [[ ! $(ssh::connected "github.com") ]]; then
            return 1
        fi
    fi
    return 0
}

# Make the index page
app::make_index() {

    curl http://lawrancej.github.io/starterupper/index.html 2> /dev/null > $REPO-index.html 
#    cp ~/projects/starterupper/index.html $REPO-index.html

    sed -e "s/REPOSITORY/$REPO/g" \
    -e "s/USER_EMAIL/$(email::get)/g" \
    -e "s/FULL_NAME/$(full_name::get)/g" \
    -e "s/USER_NAME/$(username::get)/g" \
    -e "s/INSTRUCTOR_GITHUB/$INSTRUCTOR_GITHUB/g" \
    -e "s/PUBLIC_KEY/$(ssh::getPublicKeyForSed)/g" \
    -e "s/HOSTNAME/$(hostname)/g" \
    $REPO-index.html > temp.html
    rm "$REPO-index.html"
}

# Given a POST request, receive the data
app::receive_data() {
    request::post_form_data "$1" | while read parameter; do
        local key="$(parameter::key "$parameter")"
        local value="$(parameter::value "$parameter")"
        case "$key" in
            "user.name" )    full_name::set "$value" ;;
            "user.email" )   email::set "$value" ;;
            "github.login" ) host_login::set "github" "$value" ;;
        esac
    done
}

app::index() {
    app::receive_data "$1"
    
    git::configure_remotes "github.com" "$(host_login::get "github")" "$INSTRUCTOR_GITHUB" > /dev/null
    github::connected
    git::push >&2
    
    app::make_index
    server::send_file "temp.html"
}

# Return the browser to the browser for disabled JavaScript troubleshooting
app::browser() {
    local request="$1"
    local agent="$(request::lookup "$request" "User-Agent")"
    case "$agent" in
        *MSIE* | *Trident* )
            server::send_string ".firefox, .chrome {display: none;}" "browser.css" ;;
        *Firefox* )
            server::send_string ".chrome, .msie {display: none;}" "browser.css" ;;
        *Chrome* )
            server::send_string ".firefox, .msie {display: none;}" "browser.css" ;;
    esac
}

# Setup local repositories
app::setup() {
    printf "Receiving data..." >&2
    app::receive_data "$1"
    echo -e "                                                          [\e[1;32mOK\e[0m]" >&2

    git::configure_remotes "github.com" "$(host_login::get github)" "$INSTRUCTOR_GITHUB" > /dev/null

    local response=""
    printf "Responding to request..." >&2
    read -r -d '' response <<-EOF
{
  "name": "$(full_name::get)",
  "email": "$(email::get)",
  "github": "$(host_login::get "github")",
  "clone": ${cloned},
  "status": true
}
EOF
    server::send_string "$response" "response.json"
    echo -e "                                                   [\e[1;32mOK\e[0m]" >&2
    
    sleep 1

    github::connected
    git::push >&2
    if [[ $? -eq 0 ]]; then
        app::shutdown
    fi
}

# Handle requests from the browser
app::router() {
    local request="$1"
    local target="$(request::file "$request")"
    case "$target" in
        "/" )           app::index "$request" ;;
        "browser.css" ) app::browser "$request" ;;
        "setup" )       app::setup "$request" ;;
        * )             server::send_file "$target"
    esac
}

app::url() {
    printf "file://$(pwd | sed -e "s/^\\/c/\\/c:/")/temp.html"
}

main() {
    # Go into the home directory
    pushd ~ > /dev/null
    
    # Make web page
    printf "Please wait, gathering information..."
    ssh::configure
    app::make_index
    echo -e "                                      [\e[1;32mOK\e[0m]"
    
    # Clone upstream
    printf "Cloning upstream..."
    git::clone_upstream "github.com" "$INSTRUCTOR_GITHUB"
    if [[ $cloned == true ]]; then
        echo -e "                                                        [\e[1;32mOK\e[0m]"
    else
        echo -e "                                                    [\e[1;31mFAILED\e[0m]"
    fi

    # Open setup page
    utility::paste "$(app::url)"
    echo "Opening $(app::url) in a web browser."
    utility::fileOpen temp.html

    echo -e "Starting local web server at http://localhost:8080...                      [\e[1;32mOK\e[0m]"
    server::start "app::router"
    
    # Go back where we were
    popd > /dev/null
}

export TERM=xterm
main
