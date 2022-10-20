



## SDCard

- 存在不同slot, slot0用于片上flash, 所以这里实际上不可用.

```Python
class machine.SDCard(
	_slot=1_, _width=1_, _cd=None_, _wp=None_,
	_sck=None_, _miso=None_, _mosi=None_, _cs=None_,
	_freq=20000000_)
# usage: instance the SDCard and where to mount
os.mount(machine.SDCard(), "/sd")
```

| Slot   | 0   | 1   | 2   | 3   |
| ------ | --- | --- | --- | --- |
| Signal | Pin | Pin | Pin | Pin |
| SCK    | 6   | 14  | 18  | 14  |
| CMD    | 11  | 15  |     |     |
| CS     |     |     | 5   | 15  |
| MISO   |     |     | 19  | 12  |
| MOSI   |     |     | 23  | 13  |
| D0     | 7   | 2   |     |     |
| D1     | 8   | 4   |     |     |
| D2     | 9   | 12  |     |     |
| D3     | 10  | 13  |     |     |
| D4     | 16  |     |     |     |
| D5     | 17  |     |     |     |
| D6     | 5   |     |     |     |
| D7     | 18  |     |     |     |

copied from [SDCard 类 – 安全数字存储卡 - microPython zh docs](http://www.micropython.com.cn/en/latet/library/machine.SDCard.html)


