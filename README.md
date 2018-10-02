# MyIRC

**Subject [here](https://github.com/thibautcornolti/MyIRC/raw/master/Subject.pdf)**

![example](https://i.imgur.com/HuTJ3z1.png)

## Usage

Shell:
```
$> ./server 6667    # open an IRC server
$> ./client         # open the client
```

Client - command list:
```
> /server <ip>:<port>                     # connect to a server
> /nick <new nickname>                    # set a nickname
> /list                                   # channel list with users
> /join <#channel>                        # join an irc channel
> /part [#channel]                        # leave an irc channel or the current one
> /users                                  # list the connected users
> /names [#channel]                       # list users in a channel or the current one
> /msg <#channel / nickname> <msg>        # send a message to a channel or a user
> /send_file <#channel / nickname> <file> # send a file to a channel or a user
> /accept_file <#channel / nickname>      # accept the last file from a channel or a user
```

## Authors

* Arthur Knoepflin
* Thibaut Cornolti
