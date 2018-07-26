import urllib2
import re
from bs4 import BeautifulSoup
def Openp(url):
    mHead={}
    request=urllib2.Request(url,headers=mHead)
    f=urllib2.urlopen(request)
    data=f.read()
    return data
def zhengwen(page):
    w=BeautifulSoup(page,"html.parser")
    ww=w.find_all(class_="p")[0].get_text()
    return ww
def urlall(page):
    mm=[]
    w=BeautifulSoup(page,"html.parser")
    ww=w.find_all(href=re.compile("chapter"))
    for ll in ww:
        mm.append("http://www.17k.com/"+ll['href'])
    return mm
def write1(path,data):
    f=open(path,"a+",encode="GBK")
    f.write(data)
    f.close()

if __name__=="__main__":
    f=Openp("http://www.17k.com/list/2832767.html")
   # print zhengwen(f)
    ff= urlall(f)
    for ll in ff:
        m=Openp(ll)
        data=zhengwen(m)
        write1("qwe.txt".data)
        print 1
