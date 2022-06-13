@echo off
path = %path%;.\..\..\thirdparty\libprotobuf_win64\bin
protoc.exe --experimental_allow_proto3_optional ./addressbook.proto --cpp_out=./

