## Universal remote controller

Desktop application and android application for remote control computer in local network

Приложение для десктопа принимает команды от android-приложения по UDP и запускает назначенные пользователем программы, это мотут быть консольные программы или программы для десктопа.

Пример конфигурации приложения для десктопа:

```
Volume up (default);4001;smplayer -send-action increase_volume
Volume down (default);4002;smplayer -send-action decrease_volume
Power off (default);1000;shutdown now
Next (default);2000;smplayer -send-action play_next
Prev (default);2001;smplayer -send-action play_prev
Play (default);2002;smplayer -send-action play
Pause (default);2003;smplayer -send-action pause
```

Author TechnoMag, may 2022
