#!/bin/bash
extensions::download() {
    curl http://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz > SDL2_image-devel-2.0.0-mingw.tar.gz
    curl http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.0-mingw.tar.gz > SDL2_mixer-devel-2.0.0-mingw.tar.gz
    curl http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.12-mingw.tar.gz > SDL2_ttf-devel-2.0.12-mingw.tar.gz
    curl http://www.libsdl.org/projects/SDL_net/release/SDL2_net-devel-2.0.0-mingw.tar.gz > SDL2_net-devel-2.0.0-mingw.tar.gz
}
extensions::extract() {
    tar -xzvf SDL2_image-devel-2.0.0-mingw.tar.gz
    tar -xzvf SDL2_mixer-devel-2.0.0-mingw.tar.gz
    tar -xzvf SDL2_ttf-devel-2.0.12-mingw.tar.gz
    tar -xzvf SDL2_net-devel-2.0.0-mingw.tar.gz
}
extensions::install() {
    local dest="$(which gcc)"
    dest="${dest%/bin/gcc}"
    if [[ -d $dest/lib64 ]]; then
        find SDL2* | grep x86_64 | grep mingw32$ | while read library; do
            pushd $library
            mv lib lib64
            cp -R bin/ include/ lib64/ $dest
            popd
        done
    else
        find SDL2* | grep 686 | grep mingw32$ | while read library; do
            pushd $library
            cp -R bin/ include/ lib/ $dest
            popd
        done
    fi
}
extensions::clean() {
    rm -rf SDL2_*-mingw.tar.gz
    rm -rf SDL2_*-2.0.*
}
main() {
    cd ~
    extensions::download
    extensions::extract
    extensions::install
    extensions::clean
}
main
