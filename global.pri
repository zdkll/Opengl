ROOT_PATH = $$PWD

LIB_PATH = $$ROOT_PATH/lib
BIN_PATH = $$ROOT_PATH/bin

equals(TEMPLATE,lib){
     DESTDIR = $$LIB_PATH
}else{
    DESTDIR = $$BIN_PATH
}
