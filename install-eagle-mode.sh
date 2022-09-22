#!/usr/bin/env bash
set -euo pipefail

function install_eagle_mode() {
    local destination_directory
    destination_directory="${1}"

    if [ -z "${destination_directory}" ]; then

        printf 'A %s is expected as "%s" (%s)' 'non-empty string' "first argument" "eagle mode destination directory" 1>&2

        return 1

    fi

    if [ -e "${destination_directory}" ] && [ ! -d "${destination_directory}" ]; then

        printf 'A %s is expected as "%s" (%s)' 'directory' "first argument" "eagle mode destination directory" 1>&2

        return 1

    fi

    mkdir --parents "${destination_directory}"

    echo sudo apt install --assume-yes \
        libvlc-dev \
        libpoppler-glib-dev \
        librsvg2-dev \
        xterm \
        libwebp-dev

    apt install --assume-yes \
        libvlc-dev \
        libpoppler-glib-dev \
        librsvg2-dev \
        xterm \
        libwebp-dev

    local libraries
    libraries=':/usr/include/gtk-3.0:/usr/include/pango-1.0:/usr/lib/x86_64-linux-gnu/glib-2.0/include:/usr/include/glib-2.0'

    (

        CPATH="$CPATH:/usr/include/atk-1.0:/usr/include/gdk-pixbuf-2.0:/usr/include/cairo:/usr/include/harfbuzz:${libraries}"
        /bin/bash -c 'perl make.pl build && perl make.pl install dir="'"${destination_directory}"'"'

    )
}
alias install-eagle-mode='install_eagle_mode'

set +euo pipefail
