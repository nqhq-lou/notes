---
title: accelerate microPython
tags: [microPython/accelerate]
---


- microPython needs for speed
- Optimisation steps:
	- Identify the slowest section of code.
	- Improve the efficiency of the Python code.
	- Use the native code emitter.
	- Use the viper code emitter.
	- Use hardware-specific optimisations.


## identify slowest section of the code

- the below code enables `@timed_function` decorator for timing
```Python
def timed_function(f, *args, **kwargs):
    myname = str(f).split(' ')[1]
    def new_func(*args, **kwargs):
        t = utime.ticks_us()
        result = f(*args, **kwargs)
        delta = utime.ticks_diff(utime.ticks_us(), t)
        print('Function {} Time = {:6.3f}ms'.format(myname, delta/1000))
        return result
    return new_func
```



## basics builtins for speed

### buffer
- not understood

### float
- calculate with `int` as much as possible
	- and finally convert to `float`
- e.g. capture ADC readings as integers values to an array quickly
	- and only convert them to `float` for signal processing

### array
- use `array` instead of `list`
- use `memory([slice2list])` to only pass a pointer instead of making a copy.


## manual improvements

### `const`
- `from micropython import const`
- similar to `#define` in C

### caching object references
- make a "association" to the object to avoid repeatedly look up the object
```Python
# example
class foo(object):
    def __init__(self):
        self.ba = bytearray(100)
    def bar(self, obj_display):
        """
        assum self.ba and obj_display.framebuffer
        will be used repeatly in this method
        """
        ba_ref = self.ba
        fb = obj_display.framebuffer
        # iterative code using these two objects
```

### garbage collection
- module `gc`
- use `gc.collect()` on a regular basis
	- instead of running gc automatically


## further possible manual settings

### Native code emitter
- by decorator ` @micropython.native`
- This causes the microPython compiler to emit native CPU opcodes rather than bytecode.

```Python
@micropython.native
def foo(self, arg):
    buf = self.linebuf # Cached object
    # code below
```

There are certain limitations in the current implementation of the native code emitter.
-   Context managers are not supported (the `with` statement).
-   Generators are not supported.
-   If `raise` is used an argument must be supplied.
The trade-off for the improved performance (roughly twice as fast as bytecode) is an increase in compiled code size.


### Viper emitter
- Viper invokes further optimization compared to native code.
- One should use type hints


- for differences of bytecode, native code and viper
	- see [The 3 different code emitters](https://www.kickstarter.com/projects/214379695/micro-python-python-for-microcontrollers/posts/664832)
	- and [The 3 different code emitters - part 2](https://www.kickstarter.com/projects/214379695/micro-python-python-for-microcontrollers/posts/665145)


## reference
- Python docs: Maximizing Micropython speed
	- [zh-CN](http://www.86x.org/en/latet/reference/speed_python.html)
	- [en-US](https://docs.micropython.org/en/latest/reference/speed_python.html)