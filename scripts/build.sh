npm list -g node-gyp
exists=$?
if ! [ exists = 0]; then
    npm install -g node-gyp
fi
node-gyp rebuild