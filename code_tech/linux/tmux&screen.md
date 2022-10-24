
## screen

```bash
screen -S sname  # create a screen session
screen -r sname  # enter a screen session
screen -S sname -X quit  # kill by sname
```

| keyboard shortcuts | description            |
| ------------------ | ---------------------- |
| ctrl+A+D           | detach current session |
| ctrl+A+K           | kill current session   |
| more detail...     |                        |


## tmux

### logics
- terminal multiplexer
- key concepts
	- `session`, 会话, 或者说一个tmux session, 可以保留和后续加载
	- `window`, 窗口
	- `pane`, 窗格
- relations
	- $[pane \in window] \in session$
	- session为希望保留的进程
	- 一个session可以开启很多个windows
	- 一个window可以在前端的命令行程序里, 分成许多的panes
- 

### commands
```bash
# session cmd
tmux ls  # list sessions
tmux  # create a session with id 0
tmux new -s sname  # explicitly name the session, for quick reload
tmux detach  # detach current session
tmux attach -t sname|sid  # attach session by name or id
tmux a -t sname|sid  # in short
tmux switch -t sname|sid  # switch to session with sname or id
tmux rename-session -t sname_old sname_new  # rename session name
tmux rename-session -t sid sname_new  # rename session name
tmux kill-session -t sname|id  # kill session with sname or id

# windows cmd
tmux new-window -n wname  # create a new window to current session
tmux rename-window -t wname_old wname_new   # rename window name
# for more see keyboard shortcuts

# pane cmd
tmux split-window  # split to up/down windows
tmux split-window -h  # split to left/right windows
tmux swap-pane -U  # -D move cursor to panes

# others
tmux list-keys  # list all keyboard shortcuts
tmux list-commands  # list all tmux commands
tmux info  # list all tmux session info
tmux source-file ~/.tmux.conf  # reload tmux config
```

| keyboard shortcuts | equivalent cmd             | description               |
| ------------------ | -------------------------- | ------------------------- |
| ctrl+B, \[         |                            | scroll mode, quit by Q    |
| ctrl+B, D          | tmux detach                | detach current session    |
| ctrl+B, S          |                            | switch to session         |
| ctrl+D             | tmux kill-session -t sname | kill session of sname     |
| ctrl+B, C          |                            | create a new window       |
| ctrl+B, P          |                            | switch to previous window |
| ctrl+B, N          |                            | switch to next window     |
| ctrl+B, W          |                            | select window from list   |
| ctrl+B, %          |                            | left/right split          |
| ctrl+B, "          |                            | up/down split             |
| ctrl+B, ↑→↓←       |                            | change cursor pane        |
| ctrl+B+↑→↓←        |                            | change pane size          |



## install

To install GNU screen, see [[gnu_screen]] for details


## references

- [tmux教程 from CSDN](https://blog.csdn.net/CSSDCC/article/details/121231906)
- [tmux cheetsheet](https://tmuxcheatsheet.com/)
- [what are tmux  windows](https://arcolinux.com/everthing-you-need-to-know-about-tmux-windows/)
- 



