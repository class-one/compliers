#!/usr/bin/python
import re

oldpwd='by99YL17'
print('原来的密码是：by99YL17')
print('密码要求8位以上，包含大小写字母、数字和下划线')

counter=0
while 1:
	str = input('请输入新密码：')
	#mat = re.match(r'^(?=.{8,16})(?=.*[a-z])(?=.*[A-Z])(?=.*\d).*$', str)
	mat = re.match('^(?=[\s\S]{8,32}$)(?=[\s\S]*[A-Z])(?=[\s\S]*[a-z])(?=[\s\S]*[0-9]).*',str) 
	for letter in str :
		if letter in oldpwd :
			counter=counter+1
			print(counter)
	if mat and counter<3 :
		print('新密码设置成功！')
		break
	print('密码格式错误！') 
