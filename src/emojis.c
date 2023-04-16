#include "emojis.h"

wchar_t emoji(int idx) { return emojis[idx]; }

int n_emoji() {
  static int n = 0;
  if (n) {
    return n;
  }
  wchar_t *e = emojis;
  while (*e) {
    n++;
    e++;
  }
  return n;
}

wchar_t emojis[] = {
    0x1F435, // ; fully-qualified     # 🐵 monkey face
    0x1F412, // ; fully-qualified     # 🐒 monkey
    0x1F98D, // ; fully-qualified     # 🦍 gorilla
    // 0x1F9A7, // ; fully-qualified     # 🦧 orangutan
    0x1F436, // ; fully-qualified     # 🐶 dog face
    0x1F415, // ; fully-qualified     # 🐕 dog
    // 0x1F9AE, // ; fully-qualified     # 🦮 guide dog
    0x1F429, // ; fully-qualified     # 🐩 poodle
    0x1F43A, // ; fully-qualified     # 🐺 wolf
    0x1F98A, // ; fully-qualified     # 🦊 fox
    // 0x1F99D, // ; fully-qualified     # 🦝 raccoon
    0x1F431, // ; fully-qualified     # 🐱 cat face
    0x1F408, // ; fully-qualified     # 🐈 cat
    0x1F981, // ; fully-qualified     # 🦁 lion
    0x1F42F, // ; fully-qualified     # 🐯 tiger face
    0x1F405, // ; fully-qualified     # 🐅 tiger
    0x1F406, // ; fully-qualified     # 🐆 leopard
    0x1F434, // ; fully-qualified     # 🐴 horse face
    0x1F40E, // ; fully-qualified     # 🐎 horse
    0x1F984, // ; fully-qualified     # 🦄 unicorn
    0x1F993, // ; fully-qualified     # 🦓 zebra
    0x1F98C, // ; fully-qualified     # 🦌 deer
    0x1F42E, // ; fully-qualified     # 🐮 cow face
    0x1F402, // ; fully-qualified     # 🐂 ox
    0x1F403, // ; fully-qualified     # 🐃 water buffalo
    0x1F404, // ; fully-qualified     # 🐄 cow
    0x1F437, // ; fully-qualified     # 🐷 pig face
    0x1F416, // ; fully-qualified     # 🐖 pig
    0x1F417, // ; fully-qualified     # 🐗 boar
    0x1F43D, // ; fully-qualified     # 🐽 pig nose
    0x1F40F, // ; fully-qualified     # 🐏 ram
    0x1F411, // ; fully-qualified     # 🐑 ewe
    0x1F410, // ; fully-qualified     # 🐐 goat
    0x1F42A, // ; fully-qualified     # 🐪 camel
    0x1F42B, // ; fully-qualified     # 🐫 two-hump camel
    // 0x1F999, // ; fully-qualified     # 🦙 llama
    0x1F992, // ; fully-qualified     # 🦒 giraffe
    0x1F418, // ; fully-qualified     # 🐘 elephant
    0x1F98F, // ; fully-qualified     # 🦏 rhinoceros
    // 0x1F99B, // ; fully-qualified     # 🦛 hippopotamus
    0x1F42D, // ; fully-qualified     # 🐭 mouse face
    0x1F401, // ; fully-qualified     # 🐁 mouse
    0x1F400, // ; fully-qualified     # 🐀 rat
    0x1F439, // ; fully-qualified     # 🐹 hamster
    0x1F430, // ; fully-qualified     # 🐰 rabbit face
    0x1F407, // ; fully-qualified     # 🐇 rabbit
    0x1F43F, // ; unqualified         # 🐿 chipmunk
    0x1F994, // ; fully-qualified     # 🦔 hedgehog
    0x1F987, // ; fully-qualified     # 🦇 bat
    0x1F43B, // ; fully-qualified     # 🐻 bear
    0x1F428, // ; fully-qualified     # 🐨 koala
    0x1F43C, // ; fully-qualified     # 🐼 panda
    // 0x1F9A5, // ; fully-qualified     # 🦥 sloth
    // 0x1F9A6, // ; fully-qualified     # 🦦 otter
    // 0x1F9A8, // ; fully-qualified     # 🦨 skunk
    // 0x1F998, // ; fully-qualified     # 🦘 kangaroo
    // 0x1F9A1, // ; fully-qualified     # 🦡 badger
    0x1F43E, // ; fully-qualified     # 🐾 paw prints
    0x1F983, // ; fully-qualified     # 🦃 turkey
    0x1F414, // ; fully-qualified     # 🐔 chicken
    0x1F413, // ; fully-qualified     # 🐓 rooster
    0x1F423, // ; fully-qualified     # 🐣 hatching chick
    0x1F424, // ; fully-qualified     # 🐤 baby chick
    0x1F425, // ; fully-qualified     # 🐥 front-facing baby chick
    0x1F426, // ; fully-qualified     # 🐦 bird
    0x1F427, // ; fully-qualified     # 🐧 penguin
    0x1F54A, // ; unqualified         # 🕊 dove
    0x1F985, // ; fully-qualified     # 🦅 eagle
    0x1F986, // ; fully-qualified     # 🦆 duck
    // 0x1F9A2, // ; fully-qualified     # 🦢 swan
    0x1F989, // ; fully-qualified     # 🦉 owl
    // 0x1F9A9, // ; fully-qualified     # 🦩 flamingo
    // 0x1F99A, // ; fully-qualified     # 🦚 peacock
    // 0x1F99C, // ; fully-qualified     # 🦜 parrot
    0x1F438, // ; fully-qualified     # 🐸 frog
    0x1F40A, // ; fully-qualified     # 🐊 crocodile
    0x1F422, // ; fully-qualified     # 🐢 turtle
    0x1F98E, // ; fully-qualified     # 🦎 lizard
    0x1F40D, // ; fully-qualified     # 🐍 snake
    0x1F432, // ; fully-qualified     # 🐲 dragon face
    0x1F409, // ; fully-qualified     # 🐉 dragon
    0x1F995, // ; fully-qualified     # 🦕 sauropod
    0x1F996, // ; fully-qualified     # 🦖 T-Rex
    0x1F433, // ; fully-qualified     # 🐳 spouting whale
    0x1F40B, // ; fully-qualified     # 🐋 whale
    0x1F42C, // ; fully-qualified     # 🐬 dolphin
    0x1F41F, // ; fully-qualified     # 🐟 fish
    0x1F420, // ; fully-qualified     # 🐠 tropical fish
    0x1F421, // ; fully-qualified     # 🐡 blowfish
    0x1F988, // ; fully-qualified     # 🦈 shark
    0x1F419, // ; fully-qualified     # 🐙 octopus
    0x1F41A, // ; fully-qualified     # 🐚 spiral shell
    0x1F40C, // ; fully-qualified     # 🐌 snail
    0x1F98B, // ; fully-qualified     # 🦋 butterfly
    0x1F41B, // ; fully-qualified     # 🐛 bug
    0x1F41C, // ; fully-qualified     # 🐜 ant
    0x1F41D, // ; fully-qualified     # 🐝 honeybee
    0x1F41E, // ; fully-qualified     # 🐞 lady beetle
    0x1F997, // ; fully-qualified     # 🦗 cricket
    0x1F577, // ; unqualified         # 🕷 spider
    0x1F578, // ; unqualified         # 🕸 spider web
    0x1F982, // ; fully-qualified     # 🦂 scorpion
    // 0x1F99F, // ; fully-qualified     # 🦟 mosquito
    // 0x1F9A0, // ; fully-qualified     # 🦠 microbe
    0x1F490, // ; fully-qualified     # 💐 bouquet
    0x1F338, // ; fully-qualified     # 🌸 cherry blossom
    0x1F4AE, // ; fully-qualified     # 💮 white flower
    0x1F3F5, // ; unqualified         # 🏵 rosette
    0x1F339, // ; fully-qualified     # 🌹 rose
    0x1F940, // ; fully-qualified     # 🥀 wilted flower
    0x1F33A, // ; fully-qualified     # 🌺 hibiscus
    0x1F33B, // ; fully-qualified     # 🌻 sunflower
    0x1F33C, // ; fully-qualified     # 🌼 blossom
    0x1F337, // ; fully-qualified     # 🌷 tulip
    0x1F331, // ; fully-qualified     # 🌱 seedling
    0x1F332, // ; fully-qualified     # 🌲 evergreen tree
    0x1F333, // ; fully-qualified     # 🌳 deciduous tree
    0x1F334, // ; fully-qualified     # 🌴 palm tree
    0x1F335, // ; fully-qualified     # 🌵 cactus
    0x1F33E, // ; fully-qualified     # 🌾 sheaf of rice
    0x1F33F, // ; fully-qualified     # 🌿 herb
    0x1F340, // ; fully-qualified     # 🍀 four leaf clover
    0x1F341, // ; fully-qualified     # 🍁 maple leaf
    0x1F342, // ; fully-qualified     # 🍂 fallen leaf
    0x1F343, // ; fully-qualified     # 🍃 leaf fluttering in wind
    0x1F347, // ; fully-qualified     # 🍇 grapes
    0x1F348, // ; fully-qualified     # 🍈 melon
    0x1F349, // ; fully-qualified     # 🍉 watermelon
    0x1F34A, // ; fully-qualified     # 🍊 tangerine
    0x1F34B, // ; fully-qualified     # 🍋 lemon
    0x1F34C, // ; fully-qualified     # 🍌 banana
    0x1F34D, // ; fully-qualified     # 🍍 pineapple
    // 0x1F96D, // ; fully-qualified     # 🥭 mango
    0x1F34E, // ; fully-qualified     # 🍎 red apple
    0x1F34F, // ; fully-qualified     # 🍏 green apple
    0x1F350, // ; fully-qualified     # 🍐 pear
    0x1F351, // ; fully-qualified     # 🍑 peach
    0x1F352, // ; fully-qualified     # 🍒 cherries
    0x1F353, // ; fully-qualified     # 🍓 strawberry
    0x1F95D, // ; fully-qualified     # 🥝 kiwi fruit
    0x1F345, // ; fully-qualified     # 🍅 tomato
    0x1F965, // ; fully-qualified     # 🥥 coconut
    0x1F951, // ; fully-qualified     # 🥑 avocado
    0x1F346, // ; fully-qualified     # 🍆 eggplant
    0x1F954, // ; fully-qualified     # 🥔 potato
    0x1F955, // ; fully-qualified     # 🥕 carrot
    0x1F33D, // ; fully-qualified     # 🌽 ear of corn
    0x1F336, // ; unqualified         # 🌶 hot pepper
    0x1F952, // ; fully-qualified     # 🥒 cucumber
    // 0x1F96C, // ; fully-qualified     # 🥬 leafy green
    0x1F966, // ; fully-qualified     # 🥦 broccoli
    // 0x1F9C4, // ; fully-qualified     # 🧄 garlic
    // 0x1F9C5, // ; fully-qualified     # 🧅 onion
    0x1F344, // ; fully-qualified     # 🍄 mushroom
    0x1F95C, // ; fully-qualified     # 🥜 peanuts
    0x1F330, // ; fully-qualified     # 🌰 chestnut
    0x1F35E, // ; fully-qualified     # 🍞 bread
    0x1F950, // ; fully-qualified     # 🥐 croissant
    0x1F956, // ; fully-qualified     # 🥖 baguette bread
    0x1F968, // ; fully-qualified     # 🥨 pretzel
    // 0x1F96F, // ; fully-qualified     # 🥯 bagel
    0x1F95E, // ; fully-qualified     # 🥞 pancakes
    // 0x1F9C7, // ; fully-qualified     # 🧇 waffle
    0x1F9C0, // ; fully-qualified     # 🧀 cheese wedge
    0x1F356, // ; fully-qualified     # 🍖 meat on bone
    0x1F357, // ; fully-qualified     # 🍗 poultry leg
    0x1F969, // ; fully-qualified     # 🥩 cut of meat
    0x1F953, // ; fully-qualified     # 🥓 bacon
    0x1F354, // ; fully-qualified     # 🍔 hamburger
    0x1F35F, // ; fully-qualified     # 🍟 french fries
    0x1F355, // ; fully-qualified     # 🍕 pizza
    0x1F32D, // ; fully-qualified     # 🌭 hot dog
    0x1F96A, // ; fully-qualified     # 🥪 sandwich
    0x1F32E, // ; fully-qualified     # 🌮 taco
    0x1F32F, // ; fully-qualified     # 🌯 burrito
    0x1F959, // ; fully-qualified     # 🥙 stuffed flatbread
    // 0x1F9C6, // ; fully-qualified     # 🧆 falafel
    0x1F95A, // ; fully-qualified     # 🥚 egg
    0x1F373, // ; fully-qualified     # 🍳 cooking
    0x1F958, // ; fully-qualified     # 🥘 shallow pan of food
    0x1F372, // ; fully-qualified     # 🍲 pot of food
    0x1F963, // ; fully-qualified     # 🥣 bowl with spoon
    0x1F957, // ; fully-qualified     # 🥗 green salad
    0x1F37F, // ; fully-qualified     # 🍿 popcorn
    // 0x1F9C8, // ; fully-qualified     # 🧈 butter
    // 0x1F9C2, // ; fully-qualified     # 🧂 salt
    0x1F96B, // ; fully-qualified     # 🥫 canned food
    0x1F371, // ; fully-qualified     # 🍱 bento box
    0x1F358, // ; fully-qualified     # 🍘 rice cracker
    0x1F359, // ; fully-qualified     # 🍙 rice ball
    0x1F35A, // ; fully-qualified     # 🍚 cooked rice
    0x1F35B, // ; fully-qualified     # 🍛 curry rice
    0x1F35C, // ; fully-qualified     # 🍜 steaming bowl
    0x1F35D, // ; fully-qualified     # 🍝 spaghetti
    0x1F360, // ; fully-qualified     # 🍠 roasted sweet potato
    0x1F362, // ; fully-qualified     # 🍢 oden
    0x1F363, // ; fully-qualified     # 🍣 sushi
    0x1F364, // ; fully-qualified     # 🍤 fried shrimp
    0x1F365, // ; fully-qualified     # 🍥 fish cake with swirl
    // 0x1F96E, // ; fully-qualified     # 🥮 moon cake
    0x1F361, // ; fully-qualified     # 🍡 dango
    0x1F95F, // ; fully-qualified     # 🥟 dumpling
    0x1F960, // ; fully-qualified     # 🥠 fortune cookie
    0x1F961, // ; fully-qualified     # 🥡 takeout box
    0x1F980, // ; fully-qualified     # 🦀 crab
    // 0x1F99E, // ; fully-qualified     # 🦞 lobster
    0x1F990, // ; fully-qualified     # 🦐 shrimp
    0x1F991, // ; fully-qualified     # 🦑 squid
    // 0x1F9AA, // ; fully-qualified     # 🦪 oyster
    0x1F366, // ; fully-qualified     # 🍦 soft ice cream
    0x1F367, // ; fully-qualified     # 🍧 shaved ice
    0x1F368, // ; fully-qualified     # 🍨 ice cream
    0x1F369, // ; fully-qualified     # 🍩 doughnut
    0x1F36A, // ; fully-qualified     # 🍪 cookie
    0x1F382, // ; fully-qualified     # 🎂 birthday cake
    0x1F370, // ; fully-qualified     # 🍰 shortcake
    // 0x1F9C1, // ; fully-qualified     # 🧁 cupcake
    0x1F967, // ; fully-qualified     # 🥧 pie
    0x1F36B, // ; fully-qualified     # 🍫 chocolate bar
    0x1F36C, // ; fully-qualified     # 🍬 candy
    0x1F36D, // ; fully-qualified     # 🍭 lollipop
    0x1F36E, // ; fully-qualified     # 🍮 custard
    0x1F36F, // ; fully-qualified     # 🍯 honey pot
    0x1F37C, // ; fully-qualified     # 🍼 baby bottle
    0x1F95B, // ; fully-qualified     # 🥛 glass of milk
    0x2615,  // ; fully-qualified     # ☕ hot beverage
    0x1F375, // ; fully-qualified     # 🍵 teacup without handle
    0x1F376, // ; fully-qualified     # 🍶 sake
    0x1F37E, // ; fully-qualified     # 🍾 bottle with popping cork
    0x1F377, // ; fully-qualified     # 🍷 wine glass
    0x1F378, // ; fully-qualified     # 🍸 cocktail glass
    0x1F379, // ; fully-qualified     # 🍹 tropical drink
    0x1F37A, // ; fully-qualified     # 🍺 beer mug
    0x1F37B, // ; fully-qualified     # 🍻 clinking beer mugs
    0x1F942, // ; fully-qualified     # 🥂 clinking glasses
    0x1F943, // ; fully-qualified     # 🥃 tumbler glass
    0x1F964, // ; fully-qualified     # 🥤 cup with straw
    // 0x1F9C3, // ; fully-qualified     # 🧃 beverage box
    // 0x1F9C9, // ; fully-qualified     # 🧉 mate
    // 0x1F9CA, // ; fully-qualified     # 🧊 ice cube
    0x1F962, // ; fully-qualified     # 🥢 chopsticks
    0x1F37D, // ; unqualified         # 🍽 fork and knife with plate
    0x1F374, // ; fully-qualified     # 🍴 fork and knife
    0x1F944, // ; fully-qualified     # 🥄 spoon
    0x1F52A, // ; fully-qualified     # 🔪 kitchen knife
    0x1F3FA, // ; fully-qualified     # 🏺 amphora
    0x1F310, // ; fully-qualified     # 🌐 globe with meridians
    0x1F5FA, // ; unqualified         # 🗺 world map
    0x1F5FE, // ; fully-qualified     # 🗾 map of Japan
    // 0x1F9ED, // ; fully-qualified     # 🧭 compass
    0x1F3D4, // ; unqualified         # 🏔 snow-capped mountain
    0x26F0,  // ; unqualified         # ⛰ mountain
    0x1F30B, // ; fully-qualified     # 🌋 volcano
    0x1F5FB, // ; fully-qualified     # 🗻 mount fuji
    0x1F3D5, // ; unqualified         # 🏕 camping
    0x1F3D6, // ; unqualified         # 🏖 beach with umbrella
    0x1F3DC, // ; unqualified         # 🏜 desert
    0x1F3DD, // ; unqualified         # 🏝 desert island
    0x1F3DE, // ; unqualified         # 🏞 national park
    0x1F3DF, // ; unqualified         # 🏟 stadium
    0x1F3DB, // ; unqualified         # 🏛 classical building
    0x1F3D7, // ; unqualified         # 🏗 building construction
    // 0x1F9F1, // ; fully-qualified     # 🧱 brick
    0x1F3D8, // ; unqualified         # 🏘 houses
    0x1F3DA, // ; unqualified         # 🏚 derelict house
    0x1F3E0, // ; fully-qualified     # 🏠 house
    0x1F3E1, // ; fully-qualified     # 🏡 house with garden
    0x1F3E2, // ; fully-qualified     # 🏢 office building
    0x1F3E3, // ; fully-qualified     # 🏣 Japanese post office
    0x1F3E4, // ; fully-qualified     # 🏤 post office
    0x1F3E5, // ; fully-qualified     # 🏥 hospital
    0x1F3E6, // ; fully-qualified     # 🏦 bank
    0x1F3E8, // ; fully-qualified     # 🏨 hotel
    0x1F3E9, // ; fully-qualified     # 🏩 love hotel
    0x1F3EA, // ; fully-qualified     # 🏪 convenience store
    0x1F3EB, // ; fully-qualified     # 🏫 school
    0x1F3EC, // ; fully-qualified     # 🏬 department store
    0x1F3ED, // ; fully-qualified     # 🏭 factory
    0x1F3EF, // ; fully-qualified     # 🏯 Japanese castle
    0x1F3F0, // ; fully-qualified     # 🏰 castle
    0x1F492, // ; fully-qualified     # 💒 wedding
    0x1F5FC, // ; fully-qualified     # 🗼 Tokyo tower
    0x1F5FD, // ; fully-qualified     # 🗽 Statue of Liberty
    0x26F2,  // ; fully-qualified     # ⛲ fountain
    0x26FA,  // ; fully-qualified     # ⛺ tent
    0x1F301, // ; fully-qualified     # 🌁 foggy
    0x1F303, // ; fully-qualified     # 🌃 night with stars
    0x1F3D9, // ; unqualified         # 🏙 cityscape
    0x1F304, // ; fully-qualified     # 🌄 sunrise over mountains
    0x1F305, // ; fully-qualified     # 🌅 sunrise
    0x1F306, // ; fully-qualified     # 🌆 cityscape at dusk
    0x1F307, // ; fully-qualified     # 🌇 sunset
    0x1F309, // ; fully-qualified     # 🌉 bridge at night
    0x1F3A0, // ; fully-qualified     # 🎠 carousel horse
    0x1F3A1, // ; fully-qualified     # 🎡 ferris wheel
    0x1F3A2, // ; fully-qualified     # 🎢 roller coaster
    0x1F488, // ; fully-qualified     # 💈 barber pole
    0x1F3AA, // ; fully-qualified     # 🎪 circus tent
    0x1F682, // ; fully-qualified     # 🚂 locomotive
    0x1F683, // ; fully-qualified     # 🚃 railway car
    0x1F684, // ; fully-qualified     # 🚄 high-speed train
    0x1F685, // ; fully-qualified     # 🚅 bullet train
    0x1F686, // ; fully-qualified     # 🚆 train
    0x1F687, // ; fully-qualified     # 🚇 metro
    0x1F688, // ; fully-qualified     # 🚈 light rail
    0x1F689, // ; fully-qualified     # 🚉 station
    0x1F68A, // ; fully-qualified     # 🚊 tram
    0x1F69D, // ; fully-qualified     # 🚝 monorail
    0x1F69E, // ; fully-qualified     # 🚞 mountain railway
    0x1F68B, // ; fully-qualified     # 🚋 tram car
    0x1F68C, // ; fully-qualified     # 🚌 bus
    0x1F68D, // ; fully-qualified     # 🚍 oncoming bus
    0x1F68E, // ; fully-qualified     # 🚎 trolleybus
    0x1F690, // ; fully-qualified     # 🚐 minibus
    0x1F691, // ; fully-qualified     # 🚑 ambulance
    0x1F692, // ; fully-qualified     # 🚒 fire engine
    0x1F693, // ; fully-qualified     # 🚓 police car
    0x1F694, // ; fully-qualified     # 🚔 oncoming police car
    0x1F695, // ; fully-qualified     # 🚕 taxi
    0x1F696, // ; fully-qualified     # 🚖 oncoming taxi
    0x1F697, // ; fully-qualified     # 🚗 automobile
    0x1F698, // ; fully-qualified     # 🚘 oncoming automobile
    0x1F699, // ; fully-qualified     # 🚙 sport utility vehicle
    0x1F69A, // ; fully-qualified     # 🚚 delivery truck
    0x1F69B, // ; fully-qualified     # 🚛 articulated lorry
    0x1F69C, // ; fully-qualified     # 🚜 tractor
    0x1F3CE, // ; unqualified         # 🏎 racing car
    0x1F3CD, // ; unqualified         # 🏍 motorcycle
    0x1F6F5, // ; fully-qualified     # 🛵 motor scooter
    // 0x1F9BD, // ; fully-qualified     # 🦽 manual wheelchair
    // 0x1F9BC, // ; fully-qualified     # 🦼 motorized wheelchair
    // 0x1F6FA, // ; fully-qualified     # 🛺 auto rickshaw
    0x1F6B2, // ; fully-qualified     # 🚲 bicycle
    0x1F6F4, // ; fully-qualified     # 🛴 kick scooter
    // 0x1F6F9, // ; fully-qualified     # 🛹 skateboard
    0x1F68F, // ; fully-qualified     # 🚏 bus stop
    0x1F6E3, // ; unqualified         # 🛣 motorway
    0x1F6E4, // ; unqualified         # 🛤 railway track
    0x1F6E2, // ; unqualified         # 🛢 oil drum
    0x26FD,  // ; fully-qualified     # ⛽ fuel pump
    0x1F6A8, // ; fully-qualified     # 🚨 police car light
    0x1F6A5, // ; fully-qualified     # 🚥 horizontal traffic light
    0x1F6A6, // ; fully-qualified     # 🚦 vertical traffic light
    0x1F6D1, // ; fully-qualified     # 🛑 stop sign
    0x1F6A7, // ; fully-qualified     # 🚧 construction
    0x2693,  // ; fully-qualified     # ⚓ anchor
    0x26F5,  // ; fully-qualified     # ⛵ sailboat
    0x1F6F6, // ; fully-qualified     # 🛶 canoe
    0x1F6A4, // ; fully-qualified     # 🚤 speedboat
    0x1F6F3, // ; unqualified         # 🛳 passenger ship
    0x1F6E5, // ; unqualified         # 🛥 motor boat
    0x1F6A2, // ; fully-qualified     # 🚢 ship
    0x1F6E9, // ; unqualified         # 🛩 small airplane
    0x1F6EB, // ; fully-qualified     # 🛫 airplane departure
    0x1F6EC, // ; fully-qualified     # 🛬 airplane arrival
    // 0x1FA82, // ; fully-qualified     # 🪂 parachute
    0x1F4BA, // ; fully-qualified     # 💺 seat
    0x1F681, // ; fully-qualified     # 🚁 helicopter
    0x1F69F, // ; fully-qualified     # 🚟 suspension railway
    0x1F6A0, // ; fully-qualified     # 🚠 mountain cableway
    0x1F6A1, // ; fully-qualified     # 🚡 aerial tramway
    0x1F6F0, // ; unqualified         # 🛰 satellite
    0x1F680, // ; fully-qualified     # 🚀 rocket
    0x1F6F8, // ; fully-qualified     # 🛸 flying saucer
    0x1F383, // ; fully-qualified     # 🎃 jack-o-lantern
    0x1F384, // ; fully-qualified     # 🎄 Christmas tree
    0x1F386, // ; fully-qualified     # 🎆 fireworks
    0x1F387, // ; fully-qualified     # 🎇 sparkler
    // 0x1F9E8, // ; fully-qualified     # 🧨 firecracker
    0x2728,  // ; fully-qualified     # ✨ sparkles
    0x1F388, // ; fully-qualified     # 🎈 balloon
    0x1F389, // ; fully-qualified     # 🎉 party popper
    0x1F38A, // ; fully-qualified     # 🎊 confetti ball
    0x1F38B, // ; fully-qualified     # 🎋 tanabata tree
    0x1F38D, // ; fully-qualified     # 🎍 pine decoration
    0x1F38E, // ; fully-qualified     # 🎎 Japanese dolls
    0x1F38F, // ; fully-qualified     # 🎏 carp streamer
    0x1F390, // ; fully-qualified     # 🎐 wind chime
    0x1F391, // ; fully-qualified     # 🎑 moon viewing ceremony
    // 0x1F9E7, // ; fully-qualified     # 🧧 red envelope
    0x1F380, // ; fully-qualified     # 🎀 ribbon
    0x1F381, // ; fully-qualified     # 🎁 wrapped gift
    0x1F397, // ; unqualified         # 🎗 reminder ribbon
    0x1F39F, // ; unqualified         # 🎟 admission tickets
    0x1F3AB, // ; fully-qualified     # 🎫 ticket
    0x1F396, // ; unqualified         # 🎖 military medal
    0x1F3C6, // ; fully-qualified     # 🏆 trophy
    0x1F3C5, // ; fully-qualified     # 🏅 sports medal
    0x1F947, // ; fully-qualified     # 🥇 1st place medal
    0x1F948, // ; fully-qualified     # 🥈 2nd place medal
    0x1F949, // ; fully-qualified     # 🥉 3rd place medal
    0x26BD,  // ; fully-qualified     # ⚽ soccer ball
    0x26BE,  // ; fully-qualified     # ⚾ baseball
    // 0x1F94E, // ; fully-qualified     # 🥎 softball
    0x1F3C0, // ; fully-qualified     # 🏀 basketball
    0x1F3D0, // ; fully-qualified     # 🏐 volleyball
    0x1F3C8, // ; fully-qualified     # 🏈 american football
    0x1F3C9, // ; fully-qualified     # 🏉 rugby football
    0x1F3BE, // ; fully-qualified     # 🎾 tennis
    // 0x1F94F, // ; fully-qualified     # 🥏 flying disc
    0x1F3B3, // ; fully-qualified     # 🎳 bowling
    0x1F3CF, // ; fully-qualified     # 🏏 cricket game
    0x1F3D1, // ; fully-qualified     # 🏑 field hockey
    0x1F3D2, // ; fully-qualified     # 🏒 ice hockey
    // 0x1F94D, // ; fully-qualified     # 🥍 lacrosse
    0x1F3D3, // ; fully-qualified     # 🏓 ping pong
    0x1F3F8, // ; fully-qualified     # 🏸 badminton
    0x1F94A, // ; fully-qualified     # 🥊 boxing glove
    0x1F94B, // ; fully-qualified     # 🥋 martial arts uniform
    0x1F945, // ; fully-qualified     # 🥅 goal net
    0x26F3,  // ; fully-qualified     # ⛳ flag in hole
    0x1F3A3, // ; fully-qualified     # 🎣 fishing pole
    // 0x1F93F, // ; fully-qualified     # 🤿 diving mask
    0x1F3BD, // ; fully-qualified     # 🎽 running shirt
    0x1F3BF, // ; fully-qualified     # 🎿 skis
    0x1F6F7, // ; fully-qualified     # 🛷 sled
    0x1F94C, // ; fully-qualified     # 🥌 curling stone
    0x1F3AF, // ; fully-qualified     # 🎯 direct hit
    // 0x1FA80, // ; fully-qualified     # 🪀 yo-yo
    // 0x1FA81, // ; fully-qualified     # 🪁 kite
    0x1F3B1, // ; fully-qualified     # 🎱 pool 8 ball
    0x1F52E, // ; fully-qualified     # 🔮 crystal ball
    // 0x1F9FF, // ; fully-qualified     # 🧿 nazar amulet
    0x1F3AE, // ; fully-qualified     # 🎮 video game
    0x1F579, // ; unqualified         # 🕹 joystick
    0x1F3B0, // ; fully-qualified     # 🎰 slot machine
    0x1F3B2, // ; fully-qualified     # 🎲 game die
    // 0x1F9E9, // ; fully-qualified     # 🧩 puzzle piece
    // 0x1F9F8, // ; fully-qualified     # 🧸 teddy bear
    0x1F0CF, // ; fully-qualified     # 🃏 joker
    0x1F004, // ; fully-qualified     # 🀄 mahjong red dragon
    0x1F3B4, // ; fully-qualified     # 🎴 flower playing cards
    0x1F3AD, // ; fully-qualified     # 🎭 performing arts
    0x1F5BC, // ; unqualified         # 🖼 framed picture
    0x1F3A8, // ; fully-qualified     # 🎨 artist palette
    // 0x1F9F5, // ; fully-qualified     # 🧵 thread
    // 0x1F9F6, // ; fully-qualified     # 🧶 yarn
    0x1F453, // ; fully-qualified     # 👓 glasses
    0x1F576, // ; unqualified         # 🕶 sunglasses
    // 0x1F97D, // ; fully-qualified     # 🥽 goggles
    // 0x1F97C, // ; fully-qualified     # 🥼 lab coat
    // 0x1F9BA, // ; fully-qualified     # 🦺 safety vest
    0x1F454, // ; fully-qualified     # 👔 necktie
    0x1F455, // ; fully-qualified     # 👕 t-shirt
    0x1F456, // ; fully-qualified     # 👖 jeans
    0x1F9E3, // ; fully-qualified     # 🧣 scarf
    0x1F9E4, // ; fully-qualified     # 🧤 gloves
    0x1F9E5, // ; fully-qualified     # 🧥 coat
    0x1F9E6, // ; fully-qualified     # 🧦 socks
    0x1F457, // ; fully-qualified     # 👗 dress
    0x1F458, // ; fully-qualified     # 👘 kimono
    // 0x1F97B, // ; fully-qualified     # 🥻 sari
    // 0x1FA71, // ; fully-qualified     # 🩱 one-piece swimsuit
    // 0x1FA72, // ; fully-qualified     # 🩲 swim brief
    // 0x1FA73, // ; fully-qualified     # 🩳 shorts
    0x1F459, // ; fully-qualified     # 👙 bikini
    0x1F45A, // ; fully-qualified     # 👚 woman’s clothes
    0x1F45B, // ; fully-qualified     # 👛 purse
    0x1F45C, // ; fully-qualified     # 👜 handbag
    0x1F45D, // ; fully-qualified     # 👝 clutch bag
    0x1F6CD, // ; unqualified         # 🛍 shopping bags
    0x1F392, // ; fully-qualified     # 🎒 backpack
    0x1F45E, // ; fully-qualified     # 👞 man’s shoe
    0x1F45F, // ; fully-qualified     # 👟 running shoe
    // 0x1F97E, // ; fully-qualified     # 🥾 hiking boot
    // 0x1F97F, // ; fully-qualified     # 🥿 flat shoe
    0x1F460, // ; fully-qualified     # 👠 high-heeled shoe
    0x1F461, // ; fully-qualified     # 👡 woman’s sandal
    // 0x1FA70, // ; fully-qualified     # 🩰 ballet shoes
    0x1F462, // ; fully-qualified     # 👢 woman’s boot
    0x1F451, // ; fully-qualified     # 👑 crown
    0x1F452, // ; fully-qualified     # 👒 woman’s hat
    0x1F3A9, // ; fully-qualified     # 🎩 top hat
    0x1F393, // ; fully-qualified     # 🎓 graduation cap
    0x1F9E2, // ; fully-qualified     # 🧢 billed cap
    0x1F4FF, // ; fully-qualified     # 📿 prayer beads
    0x1F484, // ; fully-qualified     # 💄 lipstick
    0x1F48D, // ; fully-qualified     # 💍 ring
    0x1F48E, // ; fully-qualified     # 💎 gem stone
    0x1F507, // ; fully-qualified     # 🔇 muted speaker
    0x1F508, // ; fully-qualified     # 🔈 speaker low volume
    0x1F509, // ; fully-qualified     # 🔉 speaker medium volume
    0x1F50A, // ; fully-qualified     # 🔊 speaker high volume
    0x1F4E2, // ; fully-qualified     # 📢 loudspeaker
    0x1F4E3, // ; fully-qualified     # 📣 megaphone
    0x1F4EF, // ; fully-qualified     # 📯 postal horn
    0x1F514, // ; fully-qualified     # 🔔 bell
    0x1F515, // ; fully-qualified     # 🔕 bell with slash
    0x1F3BC, // ; fully-qualified     # 🎼 musical score
    0x1F3B5, // ; fully-qualified     # 🎵 musical note
    0x1F3B6, // ; fully-qualified     # 🎶 musical notes
    0x1F399, // ; unqualified         # 🎙 studio microphone
    0x1F39A, // ; unqualified         # 🎚 level slider
    0x1F39B, // ; unqualified         # 🎛 control knobs
    0x1F3A4, // ; fully-qualified     # 🎤 microphone
    0x1F3A7, // ; fully-qualified     # 🎧 headphone
    0x1F4FB, // ; fully-qualified     # 📻 radio
    0x1F3B7, // ; fully-qualified     # 🎷 saxophone
    0x1F3B8, // ; fully-qualified     # 🎸 guitar
    0x1F3B9, // ; fully-qualified     # 🎹 musical keyboard
    0x1F3BA, // ; fully-qualified     # 🎺 trumpet
    0x1F3BB, // ; fully-qualified     # 🎻 violin
    // 0x1FA95, // ; fully-qualified     # 🪕 banjo
    0x1F941, // ; fully-qualified     # 🥁 drum
    0x1F4F1, // ; fully-qualified     # 📱 mobile phone
    0x1F4F2, // ; fully-qualified     # 📲 mobile phone with arrow
    0x1F4DE, // ; fully-qualified     # 📞 telephone receiver
    0x1F4DF, // ; fully-qualified     # 📟 pager
    0x1F4E0, // ; fully-qualified     # 📠 fax machine
    0x1F50B, // ; fully-qualified     # 🔋 battery
    0x1F50C, // ; fully-qualified     # 🔌 electric plug
    0x1F4BB, // ; fully-qualified     # 💻 laptop computer
    0x1F5A5, // ; unqualified         # 🖥 desktop computer
    0x1F5A8, // ; unqualified         # 🖨 printer
    0x1F5B1, // ; unqualified         # 🖱 computer mouse
    0x1F5B2, // ; unqualified         # 🖲 trackball
    0x1F4BD, // ; fully-qualified     # 💽 computer disk
    0x1F4BE, // ; fully-qualified     # 💾 floppy disk
    0x1F4BF, // ; fully-qualified     # 💿 optical disk
    0x1F4C0, // ; fully-qualified     # 📀 dvd
    // 0x1F9EE, // ; fully-qualified     # 🧮 abacus
    0x1F3A5, // ; fully-qualified     # 🎥 movie camera
    0x1F39E, // ; unqualified         # 🎞 film frames
    0x1F4FD, // ; unqualified         # 📽 film projector
    0x1F3AC, // ; fully-qualified     # 🎬 clapper board
    0x1F4FA, // ; fully-qualified     # 📺 television
    0x1F4F7, // ; fully-qualified     # 📷 camera
    0x1F4F8, // ; fully-qualified     # 📸 camera with flash
    0x1F4F9, // ; fully-qualified     # 📹 video camera
    0x1F4FC, // ; fully-qualified     # 📼 videocassette
    0x1F50D, // ; fully-qualified     # 🔍 magnifying glass tilted left
    0x1F50E, // ; fully-qualified     # 🔎 magnifying glass tilted right
    0x1F56F, // ; unqualified         # 🕯 candle
    0x1F4A1, // ; fully-qualified     # 💡 light bulb
    0x1F526, // ; fully-qualified     # 🔦 flashlight
    0x1F3EE, // ; fully-qualified     # 🏮 red paper lantern
    // 0x1FA94, // ; fully-qualified     # 🪔 diya lamp
    0x1F4D4, // ; fully-qualified     # 📔 notebook with decorative cover
    0x1F4D5, // ; fully-qualified     # 📕 closed book
    0x1F4D6, // ; fully-qualified     # 📖 open book
    0x1F4D7, // ; fully-qualified     # 📗 green book
    0x1F4D8, // ; fully-qualified     # 📘 blue book
    0x1F4D9, // ; fully-qualified     # 📙 orange book
    0x1F4DA, // ; fully-qualified     # 📚 books
    0x1F4D3, // ; fully-qualified     # 📓 notebook
    0x1F4D2, // ; fully-qualified     # 📒 ledger
    0x1F4C3, // ; fully-qualified     # 📃 page with curl
    0x1F4DC, // ; fully-qualified     # 📜 scroll
    0x1F4C4, // ; fully-qualified     # 📄 page facing up
    0x1F4F0, // ; fully-qualified     # 📰 newspaper
    0x1F5DE, // ; unqualified         # 🗞 rolled-up newspaper
    0x1F4D1, // ; fully-qualified     # 📑 bookmark tabs
    0x1F516, // ; fully-qualified     # 🔖 bookmark
    0x1F3F7, // ; unqualified         # 🏷 label
    0x1F4B0, // ; fully-qualified     # 💰 money bag
    0x1F4B4, // ; fully-qualified     # 💴 yen banknote
    0x1F4B5, // ; fully-qualified     # 💵 dollar banknote
    0x1F4B6, // ; fully-qualified     # 💶 euro banknote
    0x1F4B7, // ; fully-qualified     # 💷 pound banknote
    0x1F4B8, // ; fully-qualified     # 💸 money with wings
    0x1F4B3, // ; fully-qualified     # 💳 credit card
    // 0x1F9FE, // ; fully-qualified     # 🧾 receipt
    0x1F4B9, // ; fully-qualified     # 💹 chart increasing with yen
    0x1F4B1, // ; fully-qualified     # 💱 currency exchange
    0x1F4B2, // ; fully-qualified     # 💲 heavy dollar sign
    0x1F528, // ; fully-qualified     # 🔨 hammer
    // 0x1FA93, // ; fully-qualified     # 🪓 axe
    0x1F6E0, // ; unqualified         # 🛠 hammer and wrench
    0x1F5E1, // ; unqualified         # 🗡 dagger
    0x1F52B, // ; fully-qualified     # 🔫 pistol
    0x1F3F9, // ; fully-qualified     # 🏹 bow and arrow
    0x1F6E1, // ; unqualified         # 🛡 shield
    0x1F527, // ; fully-qualified     # 🔧 wrench
    0x1F529, // ; fully-qualified     # 🔩 nut and bolt
    0x1F5DC, // ; unqualified         # 🗜 clamp
    // 0x1F9AF, // ; fully-qualified     # 🦯 probing cane
    0x1F517, // ; fully-qualified     # 🔗 link
    0x26D3,  // ; unqualified         # ⛓ chains
    // 0x1F9F0, // ; fully-qualified     # 🧰 toolbox
    // 0x1F9F2, // ; fully-qualified     # 🧲 magnet
    // 0x1F9EA, // ; fully-qualified     # 🧪 test tube
    // 0x1F9EB, // ; fully-qualified     # 🧫 petri dish
    // 0x1F9EC, // ; fully-qualified     # 🧬 dna
    0x1F52C, // ; fully-qualified     # 🔬 microscope
    0x1F52D, // ; fully-qualified     # 🔭 telescope
    0x1F4E1, // ; fully-qualified     # 📡 satellite antenna
    0x1F489, // ; fully-qualified     # 💉 syringe
    // 0x1FA78, // ; fully-qualified     # 🩸 drop of blood
    0x1F48A, // ; fully-qualified     # 💊 pill
    // 0x1FA79, // ; fully-qualified     # 🩹 adhesive bandage
    // 0x1FA7A, // ; fully-qualified     # 🩺 stethoscope
    0x1F6AA, // ; fully-qualified     # 🚪 door
    0x1F6CF, // ; unqualified         # 🛏 bed
    0x1F6CB, // ; unqualified         # 🛋 couch and lamp
    // 0x1FA91, // ; fully-qualified     # 🪑 chair
    0x1F6BD, // ; fully-qualified     # 🚽 toilet
    0x1F6BF, // ; fully-qualified     # 🚿 shower
    0x1F6C1, // ; fully-qualified     # 🛁 bathtub
    // 0x1FA92, // ; fully-qualified     # 🪒 razor
    // 0x1F9F4, // ; fully-qualified     # 🧴 lotion bottle
    // 0x1F9F7, // ; fully-qualified     # 🧷 safety pin
    // 0x1F9F9, // ; fully-qualified     # 🧹 broom
    // 0x1F9FA, // ; fully-qualified     # 🧺 basket
    // 0x1F9FB, // ; fully-qualified     # 🧻 roll of paper
    // 0x1F9FC, // ; fully-qualified     # 🧼 soap
    // 0x1F9FD, // ; fully-qualified     # 🧽 sponge
    // 0x1F9EF, // ; fully-qualified     # 🧯 fire extinguisher
    0x1F6D2, // ; fully-qualified     # 🛒 shopping cart
    0x1F6AC, // ; fully-qualified     # 🚬 cigarette
    0x1F5FF, // ; fully-qualified     # 🗿 moai
    0,       // NULL terminator
};
