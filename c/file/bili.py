# -*- encoding: utf-8 -*-
#@time:  2020/11/15 22:54
#@author: chenTao
#@file:  dnmu.py
 
import requests
import time
import io,sys
import shutil
import random

original_file = "./danmu0.txt"
local_copy = "./danmu1.txt"

#declare buffer 
buffer = ""

# import
## buffer to save the output

#buffer = io.StringIO()
#
#sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

def copy_file(src_file, dest_file):
    try:
        # Copy the source file to the destination file
        shutil.copy2(src_file, dest_file)
        print("File copied successfully.")
    except IOError:
        print("Error: file could not be copied.")
## set output encodeing with chinese

def compare_files(file1, file2):
    print("campre called\n")
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        # Read the contents of both files line by line
        f1_lines = f1.readlines()
        f2_lines = f2.readlines()

        # Get the number of lines in each file
        f1_len = len(f1_lines)
        f2_len = len(f2_lines)

        # Find the minimum number of lines between the two files
        min_len = min(f1_len, f2_len)

        # Compare each line of the two files
        for i in range(min_len):
            if f1_lines[i] != f2_lines[i]:
                print(f"Line {i+1}:")
                print(f"File 1: {f1_lines[i]}")
                print(f"File 2: {f2_lines[i]}")

        if f1_lines[f1_len-1] != f2_lines[f2_len-1]:
            with open('foo.txt', 'a') as f:
                    f.write(f1_lines[f1_len-1])
                    print(f"File 1: {f1_lines[f1_len-1]}")
                    time.sleep(3)
                    f.close()
        
#        with open('foo.txt', 'a') as f:
#                f.write(f1_lines[f1_len-1])
#                print(f"File 1: {f1_lines[f1_len-1]}")
#                time.sleep(3)
#                f.close()
        # Print the remaining lines in the longer file
        if f1_len > f2_len:
            for i in range(min_len, f1_len):
                print(f"Line {i+1}:")
                print(f"File 1: {f1_lines[i]}")
                # write the new line to foo.txt with append mode
                with open('foo.txt', 'a') as f:
                    f.write(f1_lines[i])
                    time.sleep(3)

#                with open("foo.txt", 'a', encoding='utf-8') as f:
#                    f.write(f"{f1_lines[i]}")
#                    f.close()
#                    time.sleep(5)
        elif f2_len > f1_len:
            for i in range(min_len, f2_len):
                print(f"Line {i+1}:")
                print(f"File 2: {f2_lines[i]}")
    
        # If the files have the same number of lines, print a message indicating that they are the same
        elif f1_len == f2_len:
            print("The files are the same.")
        # close files
        f1.close()
        f2.close()
 
 
class Danmu():
    def __init__(self):
        # 弹幕url
        self.url = 'https://api.live.bilibili.com/xlive/web-room/v1/dM/gethistory'
        # 请求头
        self.headers = {
            'Host': 'api.live.bilibili.com',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:78.0) Gecko/20100101 Firefox/78.0',
        }
        # 定义POST传递的参数
        self.data = {
            'roomid': '27609236',
            'csrf_token': '',
            'csrf': '',
            'visit_id': '',
        }
 
    def get_danmu(self):
        global buffer
        # 获取直播间弹幕
        html = requests.post(url=self.url, headers=self.headers, data=self.data).json()
        # 解析弹幕列表
        for content in html['data']['room']:
            # 获取昵称
            nickname = content['nickname']
            # 获取发言
            text = content['text']
            # 获取发言时间
            timeline = content['timeline']
            # 记录发言
#            msg = timeline + ' ' + nickname + ': ' + text
            msg = nickname + ': ' + text
            # save to buffer
            buffer += msg + '\n'
#            buffer.write(msg + '\n')
#            print(msg)
 
if __name__ == '__main__':
    # 创建bDanmu实例
    bDanmu = Danmu()
    i = 1
    while i < 1000:
        i += 1
        # 暂停0.5防止cpu占用过高
        # 获取弹幕
        copy_file(original_file, local_copy)
        bDanmu.get_danmu()
#        with open('danmu.txt', 'a', encoding='utf-8') as f:
#            f.write('')
#        f.close()

#        time.sleep(0.5)
#        # write buffer to file
        with open(original_file, 'w', encoding='utf-8') as f:
            f.write(buffer)
            f.close()

#            f.write(buffer.getvalue())
#        f.close()
        compare_files(original_file, local_copy)
        #empty buffer
        buffer = ""
        # close file
        # empty file 
        # clear file 
        # clear buffer
#        buffer.truncate(0)
#        buffer.seek(0)
# random numer generate
        delay = random.randint(15, 25)
        time.sleep(delay)  # Sleep for 3 seconds

#        time.sleep(20)


