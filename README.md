# olcPixelGameEngineC
This is the C port of the [olcPixelGameEngine by Javidx9](https://github.com/OneLoneCoder/olcPixelGameEngine).

Every feature of the olcPixelGameEngine up until, inclusive, v2.06
has been fully ported, with the exception of the ResourcePack. I
have personally tested it to work on Linux and Windows, however it
has NOT been extensively tested. There are likely to be countless
bugs and optomizations that will be discovered over time and I look
forward to squashing each of the bugs and optomizing!

**You only need the one file - olcPixelGameEngineC.h - included in your project!**

Everything feature of the olcPixelGameEngine up until v2.06 has been
fully ported, with the exception of the ``olc::ResourcePack`` and has
I have personally tested it to work on Linux (gcc), MinGW (gcc), and
Visual Studio 2019 Community.

# Building

## Visual Studio 2019 Community

Simply:

- Create an Empty Project.
- Add A Source File, call it whatever you want, but give it a ``.c`` extension NOT ``.cpp`` 
- Add the ``olcPixelGameEngineC.h`` header file to the project.
- Write a program and profit!

## GCC

### On Linux
```
gcc -o MyPixelGameEngineApp MyPixelGameEngineApp -lm -lX11 -lGL -lpthread -lpng
```

### On Windows (MSYS2, MinGW)
```
gcc -o MyPixelGameEngineApp.exe MyPixelGameEngineApp.c lm -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi
```

# FAQ

Your questions might end up here one day. Ask me some!

# Credits

## Official PixelGameEngine Shoutouts!
Javid has expressed his thanks to the following people whose
contributions has made the Offical PixelGameEngine what it has
become today! I too, wish to acknowledge them because without
their contributions to the original, my C port would not have
been possible.

Eremiell, slavka, gurkanctn,  Phantim, IProgramInCPP, JackOJC,
KrossX,   Huhlig,   Dragoneye,    Appa,   JustinRichardsMusic,
SliceNDice,  dandistine, Ralakus,  Gorbit99, raoul, joshinils,
benedani, Moros1138, SaladinAkara & MagetzUb for advice, ideas
and testing. 

## Moros1138's Acknowledgements.
I know it sounds like a copout, but I too want to thank each
and every one of those who contributed to the original. olcPixelGameEngine
is an amazing tool that has rekindled my desire to program
and since I've started I've learned more and more each day.

I want to thank Javid, for the community that he has built. It's an
inspiration to anybody with a brain. Of course, that's just my opinion.

I also want to thank Gusgo and TarriestPython for their encouragement
and help debugging and testing.

I want to thank MaGetzUb for his C vector implementation which made
my life **SO** much easier.

# License (OLC-3)

Copyright 2018, 2019, 2020 OneLoneCoder.com

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions 
are met:

1. Redistributions or derivations of source code must retain the above 
   copyright notice, this list of conditions and the following disclaimer.

2. Redistributions or derivative works in binary form must reproduce 
   the above copyright notice. This list of conditions and the following 
   disclaimer must be reproduced in the documentation and/or other 
   materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its 
   contributors may be used to endorse or promote products derived 
   from this software without specific prior written permission.
    
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.