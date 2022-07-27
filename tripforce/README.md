## tripforce - tripcode bruteforcer for Futaba-style imageboards
![version] ![license]

```tripforce``` is a CPU-based tripcode bruteforcer for Futaba-style imageboards, written in C.
It accomplishes this by generating random *Shift-JIS* compatible password strings using all available CPU cores and prints tripcode matches to stdout.

#### About
Many other tripcode search programs produce password strings with multi-byte Shift-JIS characters, but some modern imageboard systems have a habit of converting exotic character sets to UTF-8, rendering your passwords useless.
```tripforce``` eliminates this ambiguity by limiting the character range to US-ASCII minus ```\``` and ```~```, which have identical code-points in both Shift-JIS and UTF-8.

```tripforce``` is primarily meant for generating vanity tripcodes, but you can also use it as a CPU benchmark, because it will make your CPU run **very** hot.
For optimal speeds, don't run other CPU intensive programs while using ```tripforce```.

### Usage
```
usage:
	tripforce [OPTION] "SEARCHSTR"
help:
	(None)	 No query. Program will print random tripcodes to stdout.
	-i	 Case agnostic search.
	-h	 Display this help screen.
```

#### Tripcode limitations
* Tripcodes cannot be longer than 10 characters.
*	Tripcodes can only contain the characters ```./0-9A-Za-z```
*	10th character can only be one of these characters: ```.26AEIMQUYcgkosw```

#### Search speed
At high speeds, search functions can become a liability.
```tripforce``` provides a lightweight native search function, but if you'd like more granular control *(eg. RegEx)*, you can pipe the output of ```tripforce``` into ```grep```, but keep in mind, this is a ***massive*** bottleneck, reducing overall speed by at least 30%.

Output speed can also become a liability if ```tripforce``` is producing search string matches faster than your terminal can keep up.

At this point, it's worth noting that **case-sensitive** searches are marginally faster than **case-agnostic** and the smaller your search string, the faster you get results, unless your search string is literally 2 characters.

#### Can I use this for secure tripcodes?
Not unless you know the secret salt for the imageboard system you're targeting.

### Installation

### Building
```git clone``` into this repository or grab the latest stable release as a zip or tarball from the [Releases](https://github.com/microsounds/tripforce/releases) tab.

Run ```make``` to build, or ```sudo make install``` if you want to install it to your system.
##### Building on OS X
Apple's official distributions of ```gcc``` and ```clang``` do not support OpenMP.
Install ```clang-omp``` and ```openssl``` from Homebrew.
##### Building on Gentoo/Funtoo (via layman)
```
layman -o https://paste.installgentoo.com/view/raw/8cb971f3 -f -a gitgud
layman -s gitgud
emerge tripforce
```
##### Builds for Windows (32-bit)
* [tripforce-windows-v0.3.2.zip]
(https://github.com/microsounds/tripforce/releases/download/v0.3.2/tripforce-windows-v0.3.2.zip)
  * SHA1: 7a10f27cfe92a4f2a82e3ba7ce455786f3461ca7

#### Dependencies
* ```libssl``` for tripcode hashing using DES, make sure you have it installed before proceeding.
* ```OpenMP``` (```clang-omp``` on OS X) for multithreading ***(optional)***
  * If your compiler or platform doesn't support OpenMP, ```tripforce``` will default to single-threaded mode.

### Issues
Open an issue or pull request if you find any bugs.

### Copyright / License
```
tripforce - tripcode bruteforcer for Futaba-style imageboards
Copyright (C) 2016 microsounds <https://github.com/microsounds>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```
<sub>keywords: tripcode, bruteforcer, searcher, cracker, finder, explorer, generator, imageboard, textboard, 双葉ちゃん, futaba, 2ch, 2chan, yotsuba, 4ch, 4chan</sub>
[version]: https://img.shields.io/badge/version-v0.3.2-brightgreen.svg?style=flat)
[license]: https://img.shields.io/badge/license-GPLv3-red.svg?style=flat)
