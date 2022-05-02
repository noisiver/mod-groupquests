-- Handful of Oats (Quest: Poor Old Blanchy (Id: 151))
-- Harvest Golem (Id: 36)
DELETE FROM `creature_loot_template` WHERE `Entry`=36 AND `Item`=1528;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (36, 1528, 30, 1, 'Harvest Golem - Handful of Oats');
-- Rusty Harvest Golem (Id: 480)
DELETE FROM `creature_loot_template` WHERE `Entry`=480 AND `Item`=1528;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (480, 1528, 33, 1, 'Rusty Harvest Golem - Handful of Oats');

-- Sack of Supplies (Quest: Winds in the Desert (Id: 834))
-- Dustwind Harpy (Id: 3115)
DELETE FROM `creature_loot_template` WHERE `Entry`=3115 AND `Item`=4918;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3115, 4918, 33, 1, 'Dustwind Harpy - Sack of Supplies');
-- Dustwind Pillager (Id: 3116)
DELETE FROM `creature_loot_template` WHERE `Entry`=3116 AND `Item`=4918;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3116, 4918, 32, 1, 'Dustwind Pillager - Sack of Supplies');

-- Fungal Spores (Quest: Fungal Spores (Id: 848))
-- Oasis Snapjaw (Id: 3461)
DELETE FROM `creature_loot_template` WHERE `Entry`=3461 AND `Item`=5012;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3461, 5012, 31, 1, 'Oasis Snapjaw - Fungal Spores');

-- Deepmoss Egg (Quest: Deepmoss Spider Eggs (Id: 1069))
-- Deepmoss Creeper
DELETE FROM `creature_loot_template` WHERE `Entry`=4005 AND `Item`=5570;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4005, 5570, 33, 1, 'Deepmoss Creeper - Deepmoss Egg');
-- Deepmoss Webspinner
DELETE FROM `creature_loot_template` WHERE `Entry`=4006 AND `Item`=5570;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4006, 5570, 31, 1, 'Deepmoss Webspinner - Deepmoss Egg');
-- Deepmoss Venomspitter
DELETE FROM `creature_loot_template` WHERE `Entry`=4007 AND `Item`=5570;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4007, 5570, 30, 1, 'Deepmoss Venomspitter - Deepmoss Egg');

-- Milly's Harvest (Quest: Milly's Harvest (Id: 3904))
-- Defias Thug
DELETE FROM `creature_loot_template` WHERE `Entry`=38 AND `Item`=11119;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (38, 11119, 28, 1, 'Defias Thug - Milly\'s Harvest');

-- Cactus Apple (Quest: Galgar's Cactus Apple Surprise (Id: 4402))
-- Mottled Boar (Id: 3098)
DELETE FROM `creature_loot_template` WHERE `Entry`=3098 AND `Item`=11583;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3098, 11583, 32, 1, 'Mottled Boar - Cactus Apple');

-- Highperch Wyvern Egg (Quest: Wind Rider (Id: 4767))
-- Highperch Wyvern (Id: 4107)
DELETE FROM `creature_loot_template` WHERE `Entry`=4107 AND `Item`=12356;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4107, 12356, 38, 1, 'Highperch Wyvern - Highperch Wyvern Egg');

-- Kodo Bone (Quest: Bone Collector (Id: 5501))
-- Aged Kodo (Id: 4700)
DELETE FROM `creature_loot_template` WHERE `Entry`=4700 AND `Item`=13703;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4700, 13703, 32, 1, 'Aged Kodo - Kodo Bone');
-- Dying Kodo (Id: 4701)
DELETE FROM `creature_loot_template` WHERE `Entry`=4701 AND `Item`=13703;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4701, 13703, 33, 1, 'Dying Kodo - Kodo Bone');
-- Ancient Kodo (Id: 4702)
DELETE FROM `creature_loot_template` WHERE `Entry`=4702 AND `Item`=13703;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4702, 13703, 35, 1, 'Ancient Kodo - Kodo Bone');

-- Gaea Seed (Quest: Cycle of Rebirth (Id: 6301))
-- Pridewing Wyvern (Id: 4012)
DELETE FROM `creature_loot_template` WHERE `Entry`=4012 AND `Item`=16205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4012, 16205, 34, 1, 'Pridewing Wyvern - Gaea Seed');
-- Pridewing Skyhunter (Id: 4013)
DELETE FROM `creature_loot_template` WHERE `Entry`=4013 AND `Item`=16205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4013, 16205, 37, 1, 'Pridewing Skyhunter - Gaea Seed');
-- Pridewing Consort (Id: 4014)
DELETE FROM `creature_loot_template` WHERE `Entry`=4014 AND `Item`=16205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4014, 16205, 34, 1, 'Pridewing Consort - Gaea Seed');

-- Hellfire Spineleaf (Quest: Preparing the Salve (Id: 9345))
-- Starving Helboar (Id: 16879)
DELETE FROM `creature_loot_template` WHERE `Entry`=16879 AND `Item`=23205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16879, 23205, 29, 1, 'Starving Helboar - Hellfire Spineleaf');
-- Bonestripper Buzzard (Id: 16972)
DELETE FROM `creature_loot_template` WHERE `Entry`=16972 AND `Item`=23205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16972, 23205, 30, 1, 'Bonestripper Buzzard - Hellfire Spineleaf');

-- Digested Caracoli (Quest: A Rare Bean (Id: 9800))
-- Talbuk Thorngrazer
DELETE FROM `creature_loot_template` WHERE `Entry`=17131 AND `Item`=24419;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (17131, 24419, 31, 1, 'Talbuk Thorngrazer - Digested Caracoli');

-- Burstcap Mushroom (Quest: Burstcap Mushrooms, Mon! (Id: 9814))
-- Marshfang Slicer
DELETE FROM `creature_loot_template` WHERE `Entry`=18131 AND `Item`=24468;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18131, 24468, 30, 1, 'Marshfang Slicer - Burstcap Mushroom');

-- Salvaged Wood (Quest: I Work... For the Horde! (Id: 10086))
-- Bonechewer Scavenger
DELETE FROM `creature_loot_template` WHERE `Entry`=18952 AND `Item`=25911;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18952, 25911, 33, 1, 'Bonechewer Scavenger - Salvaged Wood');

-- Salvaged Metal (Quest: I Work... For the Horde! (Id: 10086))
-- Bonechewer Scavenger
DELETE FROM `creature_loot_template` WHERE `Entry`=18952 AND `Item`=25912;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18952, 25912, 33, 1, 'Bonechewer Scavenger - Salvaged Metal');

-- Zeppelin Debris (Quest: In Case of Emergency... (Id: 10161))
-- Deranged Helboar
DELETE FROM `creature_loot_template` WHERE `Entry`=16863 AND `Item`=28116;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `MaxCount`, `Comment`) VALUES (16863, 28116, 29, 1, 3, 'Deranged Helboar - Zeppelin Debris');
-- Starving Helboar
DELETE FROM `creature_loot_template` WHERE `Entry`=16879 AND `Item`=28116;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `MaxCount`, `Comment`) VALUES (16879, 28116, 30, 1, 3, 'Starving Helboar - Zeppelin Debris');

-- Etherlithium Matrix Crystal (Quest: You're Hired! (Id: 10186))
-- Disembodied Vindicator
DELETE FROM `creature_loot_template` WHERE `Entry`=18872 AND `Item`=28364;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18872, 28364, 32, 1, 'Disembodied Vindicator - Etherlithium Matrix Crystal');
-- Disembodied Protector
DELETE FROM `creature_loot_template` WHERE `Entry`=18873 AND `Item`=28364;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18873, 28364, 31, 1, 'Disembodied Protector - Etherlithium Matrix Crystal');

-- Ethereal Technology (Quest: Pick Your Part (Id: 10206))
-- Zaxxis Raider
DELETE FROM `creature_loot_template` WHERE `Entry`=18875 AND `Item`=28457;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18875, 28457, 34, 1, 'Zaxxis Raider - Salvaged Metal');

-- Ever-burning Ash (Quest: A Haunted History (Id: 10624), Quest: A Ghost in the Machine (Id: 10642))
-- Felfire Diemetradon
DELETE FROM `creature_loot_template` WHERE `Entry`=21408 AND `Item`=30716;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (21408, 30716, 31, 1, 'Felfire Diemetradon - Ever-burning Ash');
-- Felboar
DELETE FROM `creature_loot_template` WHERE `Entry`=21878 AND `Item`=30716;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (21878, 30716, 30, 1, 'Felboar - Ever-burning Ash');

-- Blackhoof Armaments (Quest: Arms of the Grimtotems (Id: 11148), Quest: More than Coincidence (Id: 11200))
-- Grimtotem Breaker
DELETE FROM `creature_loot_template` WHERE `Entry`=23592 AND `Item`=33071;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23592, 33071, 30, 1, 'Grimtotem Breaker - Blackhoof Armaments');
-- Grimtotem Spirit-Shifter
DELETE FROM `creature_loot_template` WHERE `Entry`=23593 AND `Item`=33071;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23593, 33071, 33, 1, 'Grimtotem Spirit-Shifter - Blackhoof Armaments');
-- Grimtotem Elder
DELETE FROM `creature_loot_template` WHERE `Entry`=23714 AND `Item`=33071;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23714, 33071, 33, 1, 'Grimtotem Elder - Blackhoof Armaments');

-- Intact Plague Container (Quest: The New Plague (Id: 11167))
-- North Fleet Sailor
DELETE FROM `creature_loot_template` WHERE `Entry`=23866 AND `Item`=33099;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23866, 33099, 32, 1, 'North Fleet Sailor - Intact Plague Container');
-- North Fleet Salvager
DELETE FROM `creature_loot_template` WHERE `Entry`=23934 AND `Item`=33099;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23934, 33099, 49, 1, 'North Fleet Salvager - Intact Plague Container');

-- Witchbane (Quest: The Witch's Bane (Id: 11181))
-- Risen Spirit
DELETE FROM `creature_loot_template` WHERE `Entry`=23554 AND `Item`=33112;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23554, 33112, 27, 1, 'Risen Spirit - Witchbane');
-- Risen Husk
DELETE FROM `creature_loot_template` WHERE `Entry`=23555 AND `Item`=33112;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23555, 33112, 29, 1, 'Risen Husk - Witchbane');

-- Wyrmtail (Quest: Catch a Dragon by the Tail (Id: 11217))
-- Searing Whelp
DELETE FROM `creature_loot_template` WHERE `Entry`=4324 AND `Item`=33175;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4324, 33175, 32, 1, 'Searing Whelp - Wyrmtail');
-- Drywallow Daggermaw
DELETE FROM `creature_loot_template` WHERE `Entry`=4345 AND `Item`=33175;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4345, 33175, 29, 1, 'Drywallow Daggermaw - Wyrmtail');

-- Spotted Hippogryph Down (Quest: Hasty Preparations (Id: 11271))
-- Shoveltusk Forager
DELETE FROM `creature_loot_template` WHERE `Entry`=29479 AND `Item`=33348;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (29479, 33348, 28, 1, 'Shoveltusk Forager - Spotted Hippogryph Down');

-- Winterfin Clam (Quest: Winterfin Commerce (Id: 11559))
-- Winterfin Shorestriker
DELETE FROM `creature_loot_template` WHERE `Entry`=25215 AND `Item`=34597;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25215, 34597, 30, 1, 'Winterfin Shorestriker - Winterfin Clam');
-- Winterfin Oracle
DELETE FROM `creature_loot_template` WHERE `Entry`=25216 AND `Item`=34597;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25216, 34597, 28, 1, 'Winterfin Oracle - Winterfin Clam');
-- Winterfin Warrior
DELETE FROM `creature_loot_template` WHERE `Entry`=25217 AND `Item`=34597;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25217, 34597, 27, 1, 'Winterfin Warrior - Winterfin Clam');

-- Warsong Munitions (Quest: Patience is a Virtue that We Don't Need (Id: 11606))
-- Nerub'ar Skitterer
DELETE FROM `creature_loot_template` WHERE `Entry`=24566 AND `Item`=34709;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (24566, 34709, 32, 1, 'Nerub\'ar Skitterer - Warsong Munitions');

-- Super Strong Metal Plate (Quest: Super Strong Metal Plates! (Id: 11644))
-- Kvaldir Mist Lord
DELETE FROM `creature_loot_template` WHERE `Entry`=25496 AND `Item`=34786;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25496, 34786, 31, 1, 'Kvaldir Mist Lord - Super Strong Metal Plate');

-- Fizzcrank Spare Parts (Quest: What's the Matter with the Transmatter? (Id: 11710), Quest: Cleaning Up the Pools (Id: 11906))
-- Scavenge-bot 004-A8
DELETE FROM `creature_loot_template` WHERE `Entry`=25752 AND `Item`=34972;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25752, 34972, 31, 1, 'Scavenge-bot 004-A8 - Fizzcrank Spare Parts');
-- Sentry-bot 57-K
DELETE FROM `creature_loot_template` WHERE `Entry`=25753 AND `Item`=34972;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25753, 34972, 28, 1, 'Sentry-bot 57-K - Fizzcrank Spare Parts');
-- Defendo-tank 66D
DELETE FROM `creature_loot_template` WHERE `Entry`=25758 AND `Item`=34972;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25758, 34972, 27, 1, 'Defendo-tank 66D - Fizzcrank Spare Parts');
-- Fizzcrank Mechagnome
DELETE FROM `creature_loot_template` WHERE `Entry`=25814 AND `Item`=34972;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25814, 34972, 29, 1, 'Fizzcrank Mechagnome - Fizzcrank Spare Parts');

-- Frostberry (Quest: Nuts for Berries (Id: 11912))
-- Coldarra Scalesworn
DELETE FROM `creature_loot_template` WHERE `Entry`=25717 AND `Item`=35492;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25717, 35492, 30, 1, 'Coldarra Scalesworn - Frostberry');
-- Coldarra Spellweaver
DELETE FROM `creature_loot_template` WHERE `Entry`=25722 AND `Item`=35492;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25722, 35492, 28, 1, 'Coldarra Spellweaver - Frostberry');
-- Coldarra Wyrmkin
DELETE FROM `creature_loot_template` WHERE `Entry`=25728 AND `Item`=35492;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25728, 35492, 27, 1, 'Coldarra Wyrmkin - Frostberry');

-- Crystallized Mana Shard (Quest: Bait and Switch (Id: 11951))
-- Coldarra Mage Slayer
DELETE FROM `creature_loot_template` WHERE `Entry`=25718 AND `Item`=35685;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25718, 35685, 80, 1, 'Coldarra Mage Slayer - Crystallized Mana Shard');

-- Scarlet Onslaught Armor (Quest: Materiel Plunder (Id: 12209))
-- Onslaught Footman
DELETE FROM `creature_loot_template` WHERE `Entry`=27203 AND `Item`=37136;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (27203, 37136, 28, 1, 'Onslaught Footman - Scarlet Onslaught Armor');

-- Scarlet Onslaught Weapon (Quest: Materiel Plunder (Id: 12209))
-- Onslaught Workman
DELETE FROM `creature_loot_template` WHERE `Entry`=27207 AND `Item`=37137;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (27207, 37137, 79, 1, 'Onslaught Workman - Scarlet Onslaught Weapon');

-- Black Blood of Yogg-Saron Sample (Quest: Black Blood of Yogg-Saron (Id: 12039))
-- Anub'ar Underlord
DELETE FROM `creature_loot_template` WHERE `Entry`=26605 AND `Item`=36725;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (26605, 36725, 29, 1, 'Anub\'ar Underlord - Black Blood of Yogg-Saron Sample');

-- Vordrassil's Seed (Quest: Vordrassil's Seeds (Id: 12242), Quest: Vordrassil's Seeds (Id: 12250))
-- Redfang Hunter
DELETE FROM `creature_loot_template` WHERE `Entry`=26356 AND `Item`=37302;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (26356, 37302, 30, 1, 'Redfang Hunter - Vordrassil\'s Seed');
-- Frostpaw Warrior
DELETE FROM `creature_loot_template` WHERE `Entry`=26357 AND `Item`=37302;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (26357, 37302, 29, 1, 'Frostpaw Warrior - Vordrassil\'s Seed');

-- Muddlecap Fungus (Quest: Mushroom Mixer (Id: 12514))
-- Lurking Basilisk
DELETE FROM `creature_loot_template` WHERE `Entry`=28145 AND `Item`=38326;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28145, 38326, 29, 1, 'Lurking Basilisk - Muddlecap Fungus');

-- Basilisk Crystals (Quest: Gluttonous Lurkers (Id: 12527))
-- Lurking Basilisk
DELETE FROM `creature_loot_template` WHERE `Entry`=28145 AND `Item`=38382;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28145, 38382, 30, 1, 'Lurking Basilisk - Basilisk Crystals');

-- Dead Thornwood (Quest: Troll Patrol: Creature Comforts (Id: 12585), Quest: Creature Comforts (Id: 12599))
-- Lurking Basilisk
DELETE FROM `creature_loot_template` WHERE `Entry`=28145 AND `Item`=38563;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `MaxCount`, `Comment`) VALUES (28145, 38563, 33, 1, 3, 'Lurking Basilisk - Dead Thornwood');

-- Forgotten Treasure (Quest: Funding the War Effort (Id: 12303))
-- Forgotten Peasant
DELETE FROM `creature_loot_template` WHERE `Entry`=27226 AND `Item`=37580;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `MaxCount`, `Comment`) VALUES (27226, 37580, 28, 1, 3, 'Forgotten Peasant - Forgotten Treasure');

-- Banana Bunch (Quest: Some Make Lemonade, Some Make Liquor (Id: 12634))
-- Mangal Crocolisk
DELETE FROM `creature_loot_template` WHERE `Entry`=28002 AND `Item`=38653;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28002, 38653, 32, 1, 'Mangal Crocolisk - Banana Bunch');
-- Emperor Cobra
DELETE FROM `creature_loot_template` WHERE `Entry`=28011 AND `Item`=38653;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28011, 38653, 31, 1, 'Emperor Cobra - Banana Bunch');

-- Papaya (Quest: Some Make Lemonade, Some Make Liquor (Id: 12634))
-- Mangal Crocolisk
DELETE FROM `creature_loot_template` WHERE `Entry`=28002 AND `Item`=38655;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28002, 38655, 30, 1, 'Mangal Crocolisk - Papaya');
-- Emperor Cobra
DELETE FROM `creature_loot_template` WHERE `Entry`=28011 AND `Item`=38655;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28011, 38655, 29, 1, 'Emperor Cobra - Papaya');

-- Orange (Quest: Some Make Lemonade, Some Make Liquor (Id: 12634))
-- Mangal Crocolisk
DELETE FROM `creature_loot_template` WHERE `Entry`=28002 AND `Item`=38656;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28002, 38656, 30, 1, 'Mangal Crocolisk - Orange');
-- Emperor Cobra
DELETE FROM `creature_loot_template` WHERE `Entry`=28011 AND `Item`=38656;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28011, 38656, 29, 1, 'Emperor Cobra - Orange');

-- Gooey Ghoul Drool (Quest: You Can Run, But You Can't Hide (Id: 12629), Quest: Silver Lining (Id: 12643))
-- Decaying Ghoul
DELETE FROM `creature_loot_template` WHERE `Entry`=28565 AND `Item`=38687;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (28565, 38687, 31, 1, 'Decaying Ghoul - Gooey Ghoul Drool');

-- Bloodmaul Brutebane Brew (Quest: Strange Brew (Id: 10511), Quest: They Stole Me Hookah and Me Brews! (Id: 10542))
-- Bloodmaul Brewmaster
DELETE FROM `creature_loot_template` WHERE `Entry`=19957 AND `Item`=29443;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `MinCount`, `MaxCount`, `Comment`) VALUES (19957, 29443, 100, 1, 1, 2, 'Bloodmaul Brewmaster - Bloodmaul Brutebane Brew');

-- Scourge Scrap Metal (Quest: Making Something Out Of Nothing (Id: 12901))
-- Vargul Deathwaker
DELETE FROM `creature_loot_template` WHERE `Entry`=29449 AND `Item`=41399;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (29449, 41399, 31, 1, 'Vargul Deathwaker - Scourge Scrap Metal');
-- Vargul Runelord
DELETE FROM `creature_loot_template` WHERE `Entry`=29450 AND `Item`=41399;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (29450, 41399, 30, 1, 'Vargul Runelord - Scourge Scrap Metal');
-- Vargul Slayer
DELETE FROM `creature_loot_template` WHERE `Entry`=29451 AND `Item`=41399;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (29451, 41399, 28, 1, 'Vargul Slayer - Scourge Scrap Metal');
-- Vargul Blighthound
DELETE FROM `creature_loot_template` WHERE `Entry`=29452 AND `Item`=41399;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (29452, 41399, 29, 1, 'Vargul Blighthound - Scourge Scrap Metal');

-- Venomhide Ravasaur Egg (Quest: Venomhide Eggs (Id: 13887))
-- Venomhide Ravasaur
DELETE FROM `creature_loot_template` WHERE `Entry`=6508 AND `Item`=46364;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (6508, 46364, 32, 1, 'Venomhide Ravasaur - Venomhide Ravasaur Egg');
