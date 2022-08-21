from urllib.parse import urlencode
from requests import get
import urllib
import json
import numpy as np
def get_weather(today):
    riqi = today['date']
    wendu_max = today['high']
    wendu_min = today['low']
    fengxiang = today['fengxiang']
    yu = today['type']
    return riqi, wendu_min, wendu_max, fengxiang, yu
def main():
    city_data = ['上海', "北京"]
    city_num = int(input("要查询的城市编号:\n0:上海 1:北京\n"))
    tips = f"查询{city_data[city_num]}未来第几天的天气:\n0:今天 1:明天 ...最多可查询未来三天天气\n"
    day_num = int(input(tips))
    if day_num > 4:
        print("超出日期\n")
        return -1
    url = f"http://wthrcdn.etouch.cn/weather_mini?city={city_data[city_num]}"
    weather = get(url)
    data = weather.json()
    chengshi = data['data']['city']
    today = data['data']['forecast'][day_num]
    riqi, wendu_min, wendu_max, fengxiang, yu = get_weather(today)
    print("城市:", chengshi)
    print("日期:", riqi)
    print("温度为:", wendu_min, "到", wendu_max)
    print("风向:", fengxiang)``
    print("天气:", yu)
if __name__ == '__main__':
    main()