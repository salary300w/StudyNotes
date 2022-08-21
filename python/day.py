from cgi import print_directory
from selenium import webdriver
from time import sleep
from email.header import Header
from smtplib import SMTP_SSL
import datetime
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.wait import WebDriverWait  # 等待页面加载某些元素
from selenium.webdriver.support import expected_conditions as EC
import sys
# 发邮件 msg_to:接收者邮箱


def send(msg_to, message):
    # 我用的是MIMEMultipart的模式，所以可以在邮件里夹图片。
    subject = "每日健康填报"  # 主题
    msg = MIMEMultipart('related')
    # content = MIMEText('<html><body><h2>打卡成功!</h2></body></html>', 'html', 'utf-8')  # 正文
    content = MIMEText(message, 'html', 'utf-8')
    # msg = MIMEText(content)
    msg.attach(content)
    msg['Subject'] = subject
    # 发送者邮箱
    msg['From'] = "510848570@qq.com"
    msg['To'] = msg_to
    try:
        s = smtplib.SMTP_SSL("smtp.qq.com", 465)  # 邮件服务器及端口号
        # xxxxx是邮箱的校验码，不是邮箱密码，需在qq邮箱网页内自行获取。
        s.login("510848570@qq.com", "rddkjicvlfeycaeh")
        s.sendmail("510848570@qq.com", msg_to, msg.as_string())
    except:
        s.quit()
    finally:
        s.quit()
# 用户类，保存用户在打卡页面的账号和密码，及通知邮箱地址。


class Person:
    schoolNum = ""
    psw = ""
    email = ""

    def __init__(self, schoolNum, psw, email):
        self.schoolNum = schoolNum
        self.psw = psw
        self.email = email


# 新建person数组存放Person对象
person = [Person(sys.argv[1], sys.argv[2], sys.argv[3])]
# 遍历所有用户，模拟打卡操作
for per in person:
    # 因为在linux命令行里运行，所以设置无头模式在后台运行。
    while (True):
        chrome_options = Options()
        chrome_options.add_argument('--no-sandbox')
        chrome_options.add_argument('--disable-dev-shm-usage')
        chrome_options.add_argument('--headless')
        # 模拟iPhone 6，因为这个页面如果不是手机端进入的话会进入管理端。
        #chrome_options.add_argument('user-agent="Mozilla/5.0 (iPhone; CPU iPhone OS 9_1 like Mac OS X) AppleWebKit/601.1.46 (KHTML, like Gecko) Version/9.0 Mobile/13B143 Safari/601.1"')
        # 创建对象
        driver = webdriver.Chrome(options=chrome_options)
        # 清楚浏览器缓存
        try:
            # 进入网站 这里填打卡网站
            driver.get(
                "https://workflow.ecust.edu.cn/default/work/uust/zxxsmryb/mrybcn.jsp")
            wait = WebDriverWait(driver, 10)
            try:
                # 这里填账号
                wait.until(EC.presence_of_element_located(
                    (By.XPATH, '/html/body/div[4]/div[1]/div[2]/div/div[3]/div/form/p[1]/input'))).send_keys(per.schoolNum)
                # 这里填密码
                wait.until(EC.presence_of_element_located(
                    (By.XPATH, '/html/body/div[4]/div[1]/div[2]/div/div[3]/div/form/p[2]/input'))).send_keys(per.psw)
                # 这里登录
                wait.until(EC.presence_of_element_located(
                    (By.XPATH, '/html/body/div[4]/div[1]/div[2]/div/div[3]/div/form/p[5]/button'))).click()
                try:
                    # 勾选个人承诺
                    wait.until(EC.presence_of_element_located(
                        (By.XPATH, '/html/body/div/div/div[1]/div/div/div/div[2]/div/div/div/div/div/ins'))).click()
                    # 点击下一步
                    wait.until(EC.presence_of_element_located(
                        (By.XPATH, '/html/body/div/div/div[2]/div/div/button[1]'))).click()
                    try:
                        wait.until(EC.presence_of_element_located(
                            (By.XPATH, '/html/body/div[3]/div[3]/a'))).click()
                        send(per.email, "今天已经打卡！")
                        break
                    except:
                        try:
                            # 填写打卡操作
                            # 点击健康
                            wait.until(EC.presence_of_element_located(
                                (By.XPATH, '/html/body/div/div/div/div/div[1]/div[2]/div/form/div[8]/div[2]/div/div/div[2]/div/div/label[1]/div/ins'))).click()
                            # 点击现人员位置
                            wait.until(EC.presence_of_element_located(
                                (By.XPATH, '/html/body/div/div/div/div/div[1]/div[2]/div/form/div[8]/div[3]/div/div/div[2]/div/div/label[1]/div/ins'))).click()
                            # 点击行程码绿码
                            wait.until(EC.presence_of_element_located(
                                (By.XPATH, '/html/body/div/div/div/div/div[1]/div[2]/div/form/div[8]/div[4]/div/div/div[2]/div/div/label[1]/div/ins'))).click()
                            # 点击学校外出否
                            wait.until(EC.presence_of_element_located(
                                (By.XPATH, '/html/body/div/div/div/div/div[1]/div[2]/div/form/div[11]/div/div/div[2]/div/div/label[1]/div/ins'))).click()
                            # 点击提交
                            wait.until(EC.presence_of_element_located(
                                (By.XPATH, '/html/body/div/div/div/div/div[2]/div/div/button[1]'))).click()
                            # 确认信息无误
                            wait.until(EC.presence_of_element_located(
                                (By.XPATH, '/html/body/div[3]/div[3]/a[1]'))).click()
                            continue
                        except:
                            continue
                except:
                    try:
                        wait.until(EC.presence_of_element_located(
                            (By.XPATH, '/html/body/div[4]/div[1]/div[2]/div/div[3]/div/form/span')))
                        send(per.email, "账户或密码设置错误！")
                        break
                    except:
                        try:
                            wait.until(EC.presence_of_element_located(
                                (By.XPATH, '/html/body/div[4]/div[1]/div[2]/div/div[3]/div/form/p[3]/span[2]')))
                            send(per.email, "出现验证码，手动登录一次后再试。")
                            break
                        except:
                            continue
            except:
                continue
        except:
            continue
    driver.quit()
