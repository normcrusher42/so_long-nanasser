# so_long-nanasser
so_long the king...
 - why did that sound wrong actually
  - no wait here's a better one
   - that's what she- WAIT-

anyways..

so_long. Great project, terrible 2D graphic library that made me wanna kill myself I genuinely wanna know how this will run shit like miniRT and cub3D
I heard mlx is getting a well needed update for the projects (making it cross-compatible and hopefully patching its racism towards funny_based_penguin_OS)

anyways anyways..

## Credits (very important)

obviously shoulda gotten down to crediting first. 
Firstly, **Juju**, *aka Juwairiyyah my auntie (or @riyarooya on github)* && **Emran** *(@Pastifier on github)* for being my moral support throughout this journey (also helped a bit with the cross-OS check for stuff like the keycodes and flags),

**the 42 mlx documentation and a few other guides** I didn't read much of but got a gist from

**itch.io and a couple other sources** for most of the tile textures

**Just Crafting Table** *(or xdtimebg on Discord)* for sanity checking the mlx renderer on a real linux-based machine, 

**Salam Sibai** *(@SalamSibai on github)* for inspiring me to aim higher with this project (resulting in a freeze just to get more time for the bonus) and for the coding references from her so_long

**vmorena** *(@12mimimimimim on github)* for most of the coding references from her so_long

**ChatGPT** for reminding me how illiterate I am with typos and misplaced variables but helped a ton with math-involved algorithms (like the interpolated movement) and some corrections. Basically my teacher for this project lmao (we gaslit each other a lot),

**My 42 evaluators** for making me pass my evaluations `125/100` with little to no problems (in the end, still got 1/3 outstanding points ;-;)

**My friends and family in 42** for the EPIC Musical inspiration and for being an AWESOME gng <3

**Me, Nasser³** *(@Pikan or @pikagamerpro on media or @normcrusher42 in github)* for being such an unacknowledged hard-working badass 💪💪 no caffeine, close to blackhole, no grass or sunlight, made the player and boat sprite, souls mode, and instead of speedrunning the mandatory part alone also froze and spent 3 extra weeks doing the bonus (all just to get 1/3 outstanding points yall don't understand art be like shalaab he's based he gets it + YOU'RE PLAYING A GOOD GAME FOR FREE WTH THIS AINT LIKE THE STEAM REVIEWS 😭)

**Me, again, I'm not done.** for having so much patience with the project trying to pull off the impossible with mlx only to be greeted with limitations after LIMITATIONS I nearly lost my sanity working on this atp im more than ready for an ACTUAL GAME ENGINE IVE PLAYED THESE GAMES BEFO-

**Me, LET ME FIN-**

**Me, PLEASE IM NOT DONE SELF-GLAZING-**

## How does it work?
### short version: 
*give image and map, read image and map, display image and map, if `key` then update image and map, exit image and map, image and map sleeps*
### long version:
it uses a simplified (but very ***very*** buggy) version of a graphic library called minilibx which's main functionality is to render images and pixels to your screen in the most unoptimized way possible pre-patched Cyberpunk style. Deadass even read dead 2 runs lighter on my system than this bastard of a project and IT AIN'T EVEN RENDERING REALTIME WHAT DID YALL FEED THIS LIBRARY???

Let's stay positive here. This library makes displaying images straight forward and simple without making it feel like a chore and I can appreciate that about it along with the keyhooks. 
Of course first we start with parsing the map in a very strict process, using get_next_line from rank 1 to read the input map file and condition-check it at the same time to make sure its playable. Then using a path-checking technique called floodfill, known for slaughtering rank 2ers in the exam, to fill the enclosed map to ensure the player has a valid path towards the exit and all the collectables (and repeating the process again to make sure the exit doesn't block a collectable) if by the end of floodfill a collectable or exit is still found, that means floodfill had failed to reach the target object(s), *rendering* the map unplayable.

Once the parsing phase is over we get to the less complicated bit, displaying different elements in the game and being able to move :D

// the continuation later //
ok so lowkey I kinda forgot my project already its been 4 and a half months since LOL
but iirc, we store the map in an array and assign the textures to their respective value corresponding to each block in the array. (0 - floor, 1 - wall, P - player, C - collectable, E - exit, O - obstacle (bonus))
then we have mlx slap the textures following the array's rules, rendering the whole map ✨

for the non-bonus player movement, I've simply had the map redraw the player's new position in the array whilst updating the previous and current tile instead of redrawing the whole map (*OPTIMIZATION REFERENCE PEOPLE :OOO*)

for the bonus, I kinda don't remember the process exactly but from what I remember, I record the current and next tile position. Both based on the number of "floor_tile.xpm" pixels * the tile position in the array. And then calculate the distant needed to travel between tiles based on the player speed and the number of steps they take (yes both values differ because the player speed affects the movement and sprite speed while the number of steps taken will influence the number of pixels traveled in a frame)

look at `bonus/player.c` and `bonus/logic.c` for reference. Sorry if I couldn't offer much of an explanation im too tired and stressed to review the project at this time haha... 😔
feel free to contact me whenever if you want me to explain! my discord is `piikan`

## Features ✨
### Sprite animation ⬆⬅⬇➡ (in all directions) with smooth interpolation movement
### Input buffering ⏱ (you don't see that in most so_longs (￣y▽,￣)╭ ) 
### Map themes 🎭 (only map is Sea as of now)
### MLX bugs 🐛🐜 (no no trust me its a feature if you can't fix it)

## So... why did this take "so long"?

Well first things first, the parsing. That part took me forever for some reason as I had to understand the logic of grabbing the map and being able to make sure its valid and isn't too large. And when I say valid, I mean stuff like the map's shape, the characters, if the path is valid, if there're any collectables, if theres more than one player or exits, you get what I mean. But it was mainly grabbing the map file that was tuff I don't remember why but it was a hassle at first. Rest of the mlx process was a speedrun. However, the BONUS!!!! That was lots of fun to do I even froze my acc just to get more time to work on it! I had lots of ideas, and implemented a lot of functionality to it (input buffering, animations (including exit and obstacles), death obstacles, and much more!! I really love projects that let you express your creativity, unbounded by the mandatory rules. Which gets me even more psyched for MiniRT coming up! ^^ I'll never forget this milestone that I've achieved in computer graphics despite the simplicity and I aim to go even higher with miniRT, me and @ZeroQL!! hehe
