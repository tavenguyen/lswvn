# lswrp-readme

[![sampctl](https://img.shields.io/badge/sampctl-lswrp-2f2f2f.svg?style=for-the-badge)](https://github.com/tavenguyen/lswrp)

```pawn
  Copyright (C) 2022 Los Santos World Remake v2.0 - tavenguyxn (Github: tavenguyen)

    Insprition:
      - lswrp (Arashi)
      - suckless-rp (Duy Dang)
      - ScavengeSurvive (Southclaws)
 
    Founder:		
      - Bambo
      - BmTan
      - Arashi (Old) 
      

    Scripter:
      - tavenguyxn (Vietnam, Can Tho City)
      - Arashi (Vietnam, Ho Chi Minh City)
      - Huynh (Vietnam, Ho Chi Minh City)

    Supporter:
      - Duy Dang

    Mapping:
      - Toan Dank (Vietnam)

                This project was remaked by tavenguyen on 08/04/2022 | 5:00 PM
````

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

## Installation

Simply install to your project:

```bash
sampctl package install tavenguyen/lswrp
```

Include in your code and begin using the library:

```pawn
#include <lswrp>
```

## Usage

When you have downloaded it, you must open mysql server to complete first step. 
```c++
sampctl p ensure
sampctl p build
export MYSQL_HOST="localhost" MYSQL_USER="root" MYSQL_PASSWORD="root" MYSQL_DATABASE="lswrp" (you could change it whatever you want)
sampctl p run
```

<!--
Write your code documentation or examples here. If your library is documented in
the source code, direct users there. If not, list your API and describe it well
in this section. If your library is passive and has no API, simply omit this
section.
-->

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```
