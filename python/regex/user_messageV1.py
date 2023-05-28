import re

text = '你好：\问题\ 你好吗'

match = re.match(r'(.+?)：(.+\问题.+) (.+)', text)
if match:
    user_name = match.group(1)
    message = match.group(3)
    tag = True
    print(f'User name: {user_name}')
    print(f'Message: {message}')
    print(f'Tag: {tag}')
else:
    print('No match')
