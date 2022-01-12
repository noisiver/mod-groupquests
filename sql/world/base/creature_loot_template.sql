-- Handful of Oats (Quest: Poor Old Blanchy (Id: 151))
-- Harvest Golem (Id: 36)
DELETE FROM `creature_loot_template` WHERE `Entry` = 36 AND `Item` = 1528;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (36, 1528, 30, 1, 'Harvest Golem - Handful of Oats');
-- Rusty Harvest Golem (Id: 480)
DELETE FROM `creature_loot_template` WHERE `Entry` = 480 AND `Item` = 1528;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (480, 1528, 33, 1, 'Rusty Harvest Golem - Handful of Oats');

-- Sack of Supplies (Quest: Winds in the Desert (Id: 834))
-- Dustwind Harpy (Id: 3115)
DELETE FROM `creature_loot_template` WHERE `Entry` = 3115 AND `Item` = 4918;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3115, 4918, 33, 1, 'Dustwind Harpy - Sack of Supplies');
-- Dustwind Pillager (Id: 3116)
DELETE FROM `creature_loot_template` WHERE `Entry` = 3116 AND `Item` = 4918;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3116, 4918, 32, 1, 'Dustwind Pillager - Sack of Supplies');

-- Fungal Spores (Quest: Fungal Spores (Id: 848))
-- Oasis Snapjaw (Id: 3461)
DELETE FROM `creature_loot_template` WHERE `Entry` = 3461 AND `Item` = 5012;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3461, 5012, 31, 1, 'Oasis Snapjaw - Fungal Spores');

-- Deepmoss Egg (Quest: Deepmoss Spider Eggs (Id: 1069))
-- Deepmoss Creeper
DELETE FROM `creature_loot_template` WHERE `Entry` = 4005 AND `Item` = 5570;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4005, 5570, 33, 1, 'Deepmoss Creeper - Deepmoss Egg');
-- Deepmoss Webspinner
DELETE FROM `creature_loot_template` WHERE `Entry` = 4006 AND `Item` = 5570;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4006, 5570, 31, 1, 'Deepmoss Webspinner - Deepmoss Egg');
-- Deepmoss Venomspitter
DELETE FROM `creature_loot_template` WHERE `Entry` = 4007 AND `Item` = 5570;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4007, 5570, 30, 1, 'Deepmoss Venomspitter - Deepmoss Egg');

-- Milly's Harvest (Quest: Milly's Harvest (Id: 3904))
-- Defias Thug
DELETE FROM `creature_loot_template` WHERE `Entry` = 38 AND `Item` = 11119;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (38, 11119, 28, 1, 'Defias Thug - Milly\'s Harvest');

-- Cactus Apple (Quest: Galgar's Cactus Apple Surprise (Id: 4402))
-- Mottled Boar (Id: 3098)
DELETE FROM `creature_loot_template` WHERE `Entry` = 3098 AND `Item` = 11583;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3098, 11583, 32, 1, 'Mottled Boar - Cactus Apple');

-- Highperch Wyvern Egg (Quest: Wind Rider (Id: 4767))
-- Highperch Wyvern (Id: 4107)
DELETE FROM `creature_loot_template` WHERE `Entry` = 4107 AND `Item` = 12356;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4107, 12356, 38, 1, 'Highperch Wyvern - Highperch Wyvern Egg');

-- Kodo Bone (Quest: Bone Collector (Id: 5501))
-- Aged Kodo (Id: 4700)
DELETE FROM `creature_loot_template` WHERE `Entry` = 4700 AND `Item` = 13703;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4700, 13703, 32, 1, 'Aged Kodo - Kodo Bone');
-- Dying Kodo (Id: 4701)
DELETE FROM `creature_loot_template` WHERE `Entry` = 4701 AND `Item` = 13703;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4701, 13703, 33, 1, 'Dying Kodo - Kodo Bone');
-- Ancient Kodo (Id: 4702)
DELETE FROM `creature_loot_template` WHERE `Entry` = 4702 AND `Item` = 13703;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4702, 13703, 35, 1, 'Ancient Kodo - Kodo Bone');

-- Gaea Seed (Quest: Cycle of Rebirth (Id: 6301))
-- Pridewing Wyvern (Id: 4012)
DELETE FROM `creature_loot_template` WHERE `Entry` = 4012 AND `Item` = 16205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4012, 16205, 34, 1, 'Pridewing Wyvern - Gaea Seed');
-- Pridewing Skyhunter (Id: 4013)
DELETE FROM `creature_loot_template` WHERE `Entry` = 4013 AND `Item` = 16205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4013, 16205, 37, 1, 'Pridewing Skyhunter - Gaea Seed');
-- Pridewing Consort (Id: 4014)
DELETE FROM `creature_loot_template` WHERE `Entry` = 4014 AND `Item` = 16205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4014, 16205, 34, 1, 'Pridewing Consort - Gaea Seed');

-- Hellfire Spineleaf (Quest: Preparing the Salve (Id: 9345))
-- Starving Helboar (Id: 16879)
DELETE FROM `creature_loot_template` WHERE `Entry` = 16879 AND `Item` = 23205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16879, 23205, 29, 1, 'Starving Helboar - Hellfire Spineleaf');
-- Bonestripper Buzzard (Id: 16972)
DELETE FROM `creature_loot_template` WHERE `Entry` = 16972 AND `Item` = 23205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16972, 23205, 30, 1, 'Bonestripper Buzzard - Hellfire Spineleaf');

-- Digested Caracoli (Quest: A Rare Bean (Id: 9800))
-- Talbuk Thorngrazer
DELETE FROM `creature_loot_template` WHERE `Entry` = 17131 AND `Item` = 24419;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (17131, 24419, 31, 1, 'Talbuk Thorngrazer - Digested Caracoli');

-- Salvaged Wood (Quest: I Work... For the Horde! (Id: 10086))
-- Bonechewer Scavenger
DELETE FROM `creature_loot_template` WHERE `Entry` = 18952 AND `Item` = 25911;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18952, 25911, 33, 1, 'Bonechewer Scavenger - Salvaged Wood');

-- Salvaged Metal (Quest: I Work... For the Horde! (Id: 10086))
-- Bonechewer Scavenger
DELETE FROM `creature_loot_template` WHERE `Entry` = 18952 AND `Item` = 25912;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18952, 25912, 33, 1, 'Bonechewer Scavenger - Salvaged Metal');

-- Zeppelin Debris (Quest: In Case of Emergency... (Id: 10161))
-- Deranged Helboar
DELETE FROM `creature_loot_template` WHERE `Entry` = 16863 AND `Item` = 28116;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `MaxCount`, `Comment`) VALUES (16863, 28116, 29, 1, 3, 'Deranged Helboar - Zeppelin Debris');
-- Starving Helboar
DELETE FROM `creature_loot_template` WHERE `Entry` = 16879 AND `Item` = 28116;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `MaxCount`, `Comment`) VALUES (16879, 28116, 30, 1, 3, 'Starving Helboar - Zeppelin Debris');

-- Etherlithium Matrix Crystal (Quest: You're Hired! (Id: 10186))
-- Disembodied Vindicator
DELETE FROM `creature_loot_template` WHERE `Entry` = 18872 AND `Item` = 28364;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18872, 28364, 32, 1, 'Disembodied Vindicator - Etherlithium Matrix Crystal');
-- Disembodied Protector
DELETE FROM `creature_loot_template` WHERE `Entry` = 18873 AND `Item` = 28364;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18873, 28364, 31, 1, 'Disembodied Protector - Etherlithium Matrix Crystal');

-- Ethereal Technology (Quest: Pick Your Part (Id: 10206))
-- Zaxxis Raider
DELETE FROM `creature_loot_template` WHERE `Entry` = 18875 AND `Item` = 28457;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18875, 28457, 34, 1, 'Zaxxis Raider - Salvaged Metal');

-- Ever-burning Ash (Quest: A Haunted History (Id: 10624), Quest: A Ghost in the Machine (Id: 10642))
-- Felfire Diemetradon
DELETE FROM `creature_loot_template` WHERE `Entry` = 21408 AND `Item` = 30716;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (21408, 30716, 31, 1, 'Felfire Diemetradon - Ever-burning Ash');
-- Felboar
DELETE FROM `creature_loot_template` WHERE `Entry` = 21878 AND `Item` = 30716;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (21878, 30716, 30, 1, 'Felboar - Ever-burning Ash');

-- Intact Plague Container (Quest: The New Plague (Id: 11167))
-- North Fleet Sailor
DELETE FROM `creature_loot_template` WHERE `Entry` = 23866 AND `Item` = 33099;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23866, 33099, 32, 1, 'North Fleet Sailor - Intact Plague Container');
-- North Fleet Salvager
DELETE FROM `creature_loot_template` WHERE `Entry` = 23934 AND `Item` = 33099;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (23934, 33099, 49, 1, 'North Fleet Salvager - Intact Plague Container');

-- Wyrmtail (Quest: Catch a Dragon by the Tail (Id: 11217))
-- Searing Whelp
DELETE FROM `creature_loot_template` WHERE `Entry` = 4324 AND `Item` = 33175;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4324, 33175, 32, 1, 'Searing Whelp - Wyrmtail');
-- Drywallow Daggermaw
DELETE FROM `creature_loot_template` WHERE `Entry` = 4345 AND `Item` = 33175;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4345, 33175, 29, 1, 'Drywallow Daggermaw - Wyrmtail');

-- Spotted Hippogryph Down (Quest: Hasty Preparations (Id: 11271))
-- Shoveltusk Forager
DELETE FROM `creature_loot_template` WHERE `Entry` = 29479 AND `Item` = 33348;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (29479, 33348, 28, 1, 'Shoveltusk Forager - Spotted Hippogryph Down');

-- Warsong Munitions (Quest: Patience is a Virtue that We Don't Need (Id: 11606))
-- Nerub'ar Skitterer
DELETE FROM `creature_loot_template` WHERE `Entry` = 24566 AND `Item` = 34709;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (24566, 34709, 32, 1, 'Nerub\'ar Skitterer - Warsong Munitions');

-- Venomhide Ravasaur Egg (Quest: Venomhide Eggs (Id: 13887))
-- Venomhide Ravasaur
DELETE FROM `creature_loot_template` WHERE `Entry` = 6508 AND `Item` = 46364;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (6508, 46364, 32, 1, 'Venomhide Ravasaur - Venomhide Ravasaur Egg');
