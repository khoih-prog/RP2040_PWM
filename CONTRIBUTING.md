## Contributing to RP2040_PWM

### Reporting Bugs

Please report bugs in [RP2040_PWM Issues](https://github.com/khoih-prog/RP2040_PWM/issues) if you find them.

However, before reporting a bug please check through the following:

* [Existing Open Issues](https://github.com/khoih-prog/RP2040_PWM/issues) - someone might have already encountered this.

If you don't find anything, please [open a new issue](https://github.com/khoih-prog/RP2040_PWM/issues/new).

---

### How to submit a bug report

Please ensure to specify the following:

* Arduino IDE version (e.g. 1.8.19) or Platform.io version
* `RP2040` Core Version (e.g. Arduino-mbed RP2040 v3.5.4 or arduino-pico core v2.7.1)
* `RP2040` Board type (e.g. NANO_RP2040_CONNECT, RASPBERRY_PI_PICO, RASPBERRY_PI_PICO_W, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc.)
* Contextual information (e.g. what you were trying to achieve)
* Simplest possible steps to reproduce
* Anything that might be relevant in your opinion, such as:
  * Operating system (Windows, Ubuntu, etc.) and the output of `uname -a`
  * Network configuration

Please be educated, civilized and constructive as you've always been. Disrespective posts against [GitHub Code of Conduct](https://docs.github.com/en/site-policy/github-terms/github-event-code-of-conduct) will be ignored and deleted.

---

### Example

```
Arduino IDE version: 1.8.19
arduino-pico core v2.7.1
RASPBERRY_PI_PICO
OS: Ubuntu 20.04 LTS
Linux xy-Inspiron-3593 5.15.0-58-generic #64~20.04.1-Ubuntu SMP Fri Jan 6 16:42:31 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux

Context:
I encountered a crash while using this library

Steps to reproduce:
1. ...
2. ...
3. ...
4. ...
```

---

### Sending Feature Requests

Feel free to post feature requests. It's helpful if you can explain exactly why the feature would be useful.

There are usually some outstanding feature requests in the [existing issues list](https://github.com/khoih-prog/RP2040_PWM/issues?q=is%3Aopen+is%3Aissue+label%3Aenhancement), feel free to add comments to them.

---

### Sending Pull Requests

Pull Requests with changes and fixes are also welcome!

Please use the `astyle` to reformat the updated library code as follows (demo for Ubuntu Linux)

1. Change directory to the library GitHub

```
xy@xy-Inspiron-3593:~$ cd Arduino/xy/RP2040_PWM_GitHub/
xy@xy-Inspiron-3593:~/Arduino/xy/RP2040_PWM_GitHub$
```

2. Issue astyle command

```
xy@xy-Inspiron-3593:~/Arduino/xy/RP2040_PWM_GitHub$ bash utils/restyle.sh
```

