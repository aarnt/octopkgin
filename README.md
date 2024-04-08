## This is OctoPkgin, a powerful pkgin front end using Qt libs.

![Main window](https://raw.githubusercontent.com/aarnt/octopkgin/master/octopkgin-mainwindow.png)

**OctoPkgin** is a Qt based GUI front end to the [pkgin](https://pkgin.net/) package manager, derived from [Octopkg](http://tintaescura.com/projects/octopkg).
It consists of a lxqt-sudo clone called [qt-sudo](https://github.com/aarnt/qt-sudo/) used to gain root privileges and a package browser application used
to search, install, remove and update packages.
The project is compatible with [NetBSD](https://netbsd.org).


### Follow the steps bellow to compile the latest source code (you'll need curl, git and qt5 packages):

```
$ git clone https://github.com/aarnt/octopkgin
$ cd octopkgin
$ /usr/pkg/qt5/bin/qmake
$ make
# make install
```

### In order to run OctoPkgin:

```
$ octopkgin
```

Remember: OctoPkgin needs doas or sudo tool to work.


Enjoy!
