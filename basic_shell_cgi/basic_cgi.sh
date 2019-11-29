#!/bin/sh
source basic_proc.sh

echo "Content-Type:text/html;charset=utf-8"
echo ""

echo "$SCRIPT_NAME"

# get
if [ $REQUEST_METHOD = "GET" ];then
    #query_string=`tee`
    echo "get strings:"
    echo $QUERY_STRING
    echo ""
    env
    setQueryVars $QUERY_STRING
    exit 0
fi


# post
if [ $REQUEST_METHOD = "POST" ];then
        cat << AAA
    <html>
    <head>
        <title>hello world</title>
    </head>
    <body>
    <form method="post">
        编号:<input type="text" name="id"><br>
        姓名:<input type="text" name="uname"><br>
        <input type="submit">
    </form>
AAA
    #使用cat或者tee接受post的方法
    postString=`cat`
    #postString=`tee`
#    read -n $CONTENT_LENGTH postString
    echo "post strings:"
    echo $postString
    echo ""
    env
    setQueryVars $postString
    exit 0
fi

echo "unknow type $REQUEST_METHOD"
exit 0