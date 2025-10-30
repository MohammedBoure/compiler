
echo "cloning repo:"
# try ssh and fall back to http
git clone git@github.com:MohammedBoure/compiler.git || git clone https://github.com/MohammedBoure/compiler.git

zip -r --password 2222 source-code.zip compiler


zip source-code.zip readme.txt test.zip


# clean
rm  -rf compiler
rm source-code.zip
