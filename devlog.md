## Geometry Wars clone dev log

#### 12/07/2014

4:00PM
---

* Just created the main class. Thinking about how to go with the SDL wrapper.
* In the past, had some issues with the game loop and Emscripten when implementing complex logic in files other than main, trying to avoid this for this project.
* I've had the same issue before, but here I am again. Finally found the official docs: http://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlsetvideomode.html. Google kept taking me to the SDL 2.0 wiki.

5:11PM
---

* Made a commit with the new Game class being used from main. Things are starting to roll on...
* For previous SDL projects I had used some sort of SDL Event class abstraction. This time I'm trying to avoid this, since it adds complexity that the cross compiler doesn't like.
  * This means that the Game class might look convoluted, but I can manage. In the end the Game class will only implement SDL stuff.

5:43PM
---

* Done with the implementation of my Game class. Now the game handles events just the way I want (keyboard, mouse and touch for the Web part).
* Extremely distracted and tired, but managed to create the skeleton class to handle input, updates and rendering.

#### 12/09/2014

12:15AM
---

* I don't know why I started this late, I had the whole day to advance on this but procrastination seemed more appropriate.
* I found a tutorial about how to implement a Geometry Wars called Neon Vector Shooter in iOS, this looks and interesting and might demonstrate further the value of my code analysis tool.
  http://gamedevelopment.tutsplus.com/tutorials/make-a-neon-vector-shooter-for-ios-first-steps--gamedev-14316
* Most of the utility classes are in C++ with some platform specific implementations for file handling. It literally took me 2 minutes to change this.
* OpenGL context creation is almost free in iOS, not a problem for me either, I've already created my skeleton.
* Many of my paths are hard coded, this might confuse ConConJS later down the road since the directory containing the resources is a constant and not part of the file path.

12:45AM
---

* Moving in the first part the game play code, again spent a lot of time just getting the project to link properly. The amount of files I'm handling is high to maintain the project using simple text editors like pico and sublime. My make files are starting to look ugly and unmaintainble.
* Renamed my Game class to SDLWrapper, it made more sense.


1:35AM
---

* After spending almost an hour resolving reference conflicts and linking issues I've decided that I need to improve my work pipeline. Might be a good time to jump to CLion or something like that.

1:54AM
---

* Yep downloading CLion (again), my previous install had expired. I didn't want to use CMake, but seems like a good fit for the size of my project.

1:58AM
---

* Loading project from source...
* CLion already started to pickup my reference conflicts, awesome!
* The project doesn't build tho', need to define linking rules. (Oh dear!)

2:28AM
---

* So I had to RTFM of CMake to find out keywords for my project dependencies.
* Added OpenGL, Glew and SDL1.2 references. Everything feels fine but guess what it doesn't build.
* According to my compiler glDrawElements is an unresolved symbol, but everything else is alright. WTF?

2:53AM
---

* I hate you CMake (why on earth your documentation is so bad?!)
* I hate you Jetbrains, make this non-sense automatic!

3:33AM
---

* link_libraries (${OPENGL_gl_LIBRARY}) this was what I was missing!!! The worst part is that it was on the official documentation. I don't know why I chose to ignore it. Sorry CMake people for all the wrong things I said. Jetbrains you too :-P
* Everything builds and runs, I already have a ship on screen shooting bullets. Need to hookup the input, will do that tomorrow feeling very tired.

#### 12/09/2014

10:00AM
---

* Let's get input working. It should be straight forward since the manager is a singleton.

10:08AM
---

* I was right, input was simple enough to get it working in just 5 minutes.

7:48PM
---

* Alright let's keep going, the goal now is to get the enemies spawning and keep track of scores. Let's go!
* Thanks god for the diff tool. It's easy to compare which files have changed between stages of the tutorial without having to actually read the tutorial!
* Alright 14 files!

8:24PM
---

* Everytime I see a .mm file I know beforehand that there's platform specific code mixed with C++. That's not awesome but at least I get a heads up before opening the file.
* Just stubbed out the highscore implementation in PlayerStatus for now.

8:51PM
---

* Need to come back to the highscore stuff and some other timing rules for score multipliers but enemy spawning is working out just fine!
* Submitting changes and taking a break.

10:59PM
---

* Started working again, now black holes and virtual joysticks will be implemented.
* The diff showed 17 files to be updated. This is the third part of the neon vector shooter tutorial at game development tuts
  http://gamedevelopment.tutsplus.com/tutorials/make-a-neon-vector-shooter-for-ios-virtual-gamepads-and-black-holes--gamedev-14633
* This migration should be smooth since there are no platform specific code files.

11:20PM
---

* Black holes and virtual joysticks have been implemented successfully. Water break!

11:31PM
---

* It is time to implement the particle effects. This is the fourth part of the tutorial found in game development tuts for the Neon Vector Shooter for iOS
  http://gamedevelopment.tutsplus.com/tutorials/make-a-neon-vector-shooter-for-ios-particle-effects--gamedev-14635
* The diff tool identified 19 modifications. Again none seem to have iOS specific code, which will make this migration a breeze.

12:02AM
---

* Got Particles?
* YouTube break!

12:22AM
---

* This is the fifth part of the tutorial found in game development tuts for the Neon Vector Shooter for iOS.
* It's time to add the iconic Warping Grid.
* According to the diff tool 12 files need to change.
* Btw, Meld is awesome, thank God for this tool! :P

12:42AM
---

* I'm done implementing the warping grid.
* It's time to implement the time wrapper.

1:06AM
---

* The time wrapper has been implemented.
* Water break!

#### 12/10/2014

10:28PM
---

* So today is time to port the game to the Web using ConConJS.

10:58PM
---

* The tools runs properly and the game is rendering in the browser, but there is some sort of issue with my main loop and the JavaScript code hangs... Looking into it.

11:11PM
---

* I was able to get a more explicit exception regarding my program hanging... the stack is blowing up somewhere...

11:46PM
---

* Still debugging!

12:23AM
---
* Woops! Two hours in and I finally was able to narrow down the problem to the entity management.