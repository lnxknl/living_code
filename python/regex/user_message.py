import re

text = '你：你好吗'

match = re.match(r'(.+?)：(.+)', text)
if match:
    user_name = match.group(1)
    message = match.group(2)
    print(f'User name: {user_name}')
    print(f'Message: {message}')
else:
    print('No match')
