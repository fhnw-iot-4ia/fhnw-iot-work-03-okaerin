# System-Programmierung
## Hands-on zu Lektion 0
Für Slides und Code Beispiele, siehe [Lektion 0](../../../fhnw-syspr/blob/master/00/README.md)

> *Achtung: Arbeiten Sie nicht direkt auf diesem Repository.*<br/>
> *[Prüfen Sie die vorhandenen Forks, um das Repository für Ihre Klasse zu finden.](../../network/members)*

### a) Raspberry Pi Setup, 30'
Die einzelnen Schritte sind in den Slides.
* Raspberry Pi Setup via USB zum eigenen Computer.
* "Hello World" in C auf Raspberry Pi speichern.
* Den C Source Code mit gcc kompilieren.<pre>
    $ gcc -o hello hello.c
    $ ./hello</pre>
* Fertig? Bitte Nachbarn helfen.

### b) GitHub Setup, 30'
Die einzelnen Schritte sind in den Slides.
* GitHub Account einrichten, falls keiner vorhanden.
* Git (auf Raspberry) Pi installieren und konfigurieren.
* Hands-on Repo erzeugen aus [/fhnw-syspr-work-00](../../../fhnw-syspr-work-00) (siehe [Git](#git))
* D.h. dem Link folgen => Forks => Classroom Link.
* Dann das Hands-on Repo (auf Raspberry Pi) klonen.
* File hello.c in Hands-on Repo committen, pushen.

### Abgabe
* Lokale Änderungen [committen und pushen](#git).
* Review? GitHub [Issue erstellen](../../issues/new), "@tamberg" erwähnen.
* Offene Fragen ausformulieren, was geht nicht, was haben Sie versucht.
* GitHub mailt mir (@tamberg) automatisch, ich versuche in weniger als 24h zu antworten.

## Tools
### Git
Auf Ihrem Computer
* Im Hands-on Repo [Fork für ihre Klasse](../../network/members), in README.md, klicken Sie auf den _GitHub Classroom Link_.
* Sobald Sie das eben geöffnete "Assessment" annehmen, sehen Sie Ihre persönliche, private _REPO_URL_:<pre>
http://github.com/fhnw-syspr-CLASS/fhnw-syspr-work-00-USER_NAME</pre>

Auf dem Raspberry Pi
* Repository klonen<pre>
    $ cd ~
    $ git clone REPO_URL</pre>
* Neue Datei kreieren<pre>
    $ git add FILE</pre>
* Änderungen committen<pre>
    $ git commit FILE -m "Fixed all bugs"</pre>
* Änderungen hochladen<pre>
    $ git push</pre>
(Hinweis: Der Dozent sieht nun den aktuellen Stand des Repositories.)

### Nano
Auf dem Raspberry Pi
* Neue oder bestehende Datei öffnen mit $ nano FILE
* Editieren (Achtung, nano hat kein Undo)
* Speichern mit `CRTL-X` `Y` `RETURN`

### SSH
Auf Ihrem Computer
* Terminal öffnen (Mac) oder `WINDOWS` `R` cmd `RETURN` (Windows)
* SSH Session starten mit<pre>
    $ ssh pi@raspberrypi.local</pre>

## Support
- [FHNW Syspr Slack](https://fhnw-syspr.slack.com/)
