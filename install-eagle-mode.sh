#!/usr/bin/env bash
set -euo pipefail

function install_eaglemode() {
    echo sudo apt install --assume-yes \
        libvlc-dev \
        libpoppler-glib-dev \
        librsvg2-dev \
        xgerm \
        libwebp-dev

    apt install --assume-yes \
        libvlc-dev \
        libpoppler-glib-dev \
        librsvg2-dev \
        xgerm \
        libwebp-dev

    local libraries
    libraries=':/usr/include/gtk-3.0:/usr/include/pango-1.0:/usr/lib/x86_64-linux-gnu/glib-2.0/include:/usr/include/glib-2.0'

    (

        CPATH="$CPATH:/usr/include/atk-1.0:/usr/include/gdk-pixbuf-2.0:/usr/include/cairo:/usr/include/harfbuzz:${libraries}"
        /bin/bash -c 'perl make.pl build && perl make.pl install dir="${HOME}/opt/local/eaglemode"'

    )
}
alias install-eaglemode='install_eaglemode'

set +euo pipefail
