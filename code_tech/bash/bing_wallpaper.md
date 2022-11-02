

```bash
#! /bin/bash
export GIO_EXTRA_MODULES=/usr/lib/x86_64-linux-gnu/gio/modules/
dirPath=$(cd $(dirname $0); pwd)
echo $dirPath
wpPath="${dirPath}/bing_local.jpg"
echo "$0: Downloading new wallpaper to $wpPath"
wpURL=`wget -q -O - 'https://bing.ioliu.cn/v1/rand?type=json' | jq -r '.[] | .url' | grep 'http'`
echo $wpURL
wget -q $wpURL -O $wpPath
# wget -q -O $picPath $(wget -q -O - 'https://bing.ioliu.cn/v1/rand?type=json' | jq -r '.[] | .url' | grep 'http')
gsettings set org.gnome.desktop.background picture-uri $wpPath
echo "$0: wallpaper set!"
```