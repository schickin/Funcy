#!/bin/sh

echo "Processing $1"
mv "$1" "$1.bak"
cat > "$1" <<EOF
//           Copyright Thomas Schickinger, 2013
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

EOF
cat "$1.bak" >> "$1"
