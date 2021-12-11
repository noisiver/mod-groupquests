-- Taillasher Egg (Quest: Break a Few Eggs (Id: 815))
DELETE FROM `creature_loot_template` WHERE `Entry`=3122 AND `Item`=4890;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3122, 4890, 48, 1, 'Bloodtalon Taillasher - Taillasher Egg');

-- Sack of Supplies (Quest: Winds in the Desert (Id: 834))
DELETE FROM `creature_loot_template` WHERE `Entry`=3115 AND `Item`=4918;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3115, 4918, 36, 1, 'Dustwind Harpy - Sack of Supplies');
DELETE FROM `creature_loot_template` WHERE `Entry`=3116 AND `Item`=4918;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3116, 4918, 35, 1, 'Dustwind Pillager - Sack of Supplies');

-- Fungal Spores (Quest: Fungal Spores (Id: 848))
DELETE FROM `creature_loot_template` WHERE `Entry`=3461 AND `Item`=5012;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3461, 5012, 39, 1, 'Oasis Snapjaw - Fungal Spores');

-- Nugget Slug (Quest: Nugget Slugs (Id: 3922))
DELETE FROM `creature_loot_template` WHERE `Entry`=3282 AND `Item`=11143;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3282, 11143, 41, 1, 'Venture Co. Mercenary - Nugget Slug');
DELETE FROM `creature_loot_template` WHERE `Entry`=3284 AND `Item`=11143;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3284, 11143, 42, 1, 'Venture Co. Drudger - Nugget Slug');

-- Gaea Seed (Quest: Cycle of Rebirth (Id: 6301))
DELETE FROM `creature_loot_template` WHERE `Entry`=4012 AND `Item`=16205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4012, 16205, 42, 1, 'Pridewing Wyvern - Gaea Seed');
DELETE FROM `creature_loot_template` WHERE `Entry`=4014 AND `Item`=16205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4014, 16205, 43, 1, 'Pridewing Consort - Gaea Seed');

-- Troll Charm (Quest: Troll Charm (Id: 6462))
DELETE FROM `creature_loot_template` WHERE `Entry`=3921 AND `Item`=16602;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3921, 16602, 39, 1, 'Thistlefur Ursa - Troll Charm');
DELETE FROM `creature_loot_template` WHERE `Entry`=3922 AND `Item`=16602;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3922, 16602, 40, 1, 'Thistlefur Totemic - Troll Charm');
DELETE FROM `creature_loot_template` WHERE `Entry`=3923 AND `Item`=16602;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3923, 16602, 38, 1, 'Thistlefur Den Watcher - Troll Charm');

-- Mudsnout Blossoms (Quest: Elixir of Agony (Id: 509))
DELETE FROM `creature_loot_template` WHERE `Entry`=2372 AND `Item`=3502;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (2372, 3502, 46, 1, 'Mudsnout Gnoll - Mudsnout Blossoms');
DELETE FROM `creature_loot_template` WHERE `Entry`=2373 AND `Item`=3502;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (2373, 3502, 48, 1, 'Mudsnout Shaman - Mudsnout Blossoms');

-- Highperch Wyvern Egg (Quest: Wind Rider (Id: 4767))
DELETE FROM `creature_loot_template` WHERE `Entry`=4107 AND `Item`=12356;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4107, 12356, 41, 1, 'Highperch Wyvern - Highperch Wyvern Egg');
DELETE FROM `creature_loot_template` WHERE `Entry`=4109 AND `Item`=12356;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4109, 12356, 43, 1, 'Highperch Consort - Highperch Wyvern Egg');
DELETE FROM `creature_loot_template` WHERE `Entry`=4110 AND `Item`=12356;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (4110, 12356, 44, 1, 'Highperch Patriarch - Highperch Wyvern Egg');

-- Incendia Agave (Quest: Sacred Fire (Id: 5062))
DELETE FROM `creature_loot_template` WHERE `Entry`=10756 AND `Item`=12732;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (10756, 12732, 42, 1, 'Scalding Elemental - Incendia Agave');
DELETE FROM `creature_loot_template` WHERE `Entry`=10757 AND `Item`=12732;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (10757, 12732, 44, 1, 'Boiling Elemental - Incendia Agave');

-- Witchbane (Quest: The Witch's Bane (11181))
UPDATE `creature_loot_template` SET `Chance`=43 WHERE `Entry`=23554 AND `Item`=33112;
UPDATE `creature_loot_template` SET `Chance`=46 WHERE `Entry`=23555 AND `Item`=33112;

-- Wyrmtail (Quest: Catch a Dragon by the Tail (Id: 11217))
UPDATE `creature_loot_template` SET `Chance`=42 WHERE `Entry`=4345 AND `Item`=33175;

-- Blackhoof Armaments (Quest: More than Coincidence (11200))
UPDATE `creature_loot_template` SET `Chance`=41 WHERE `Entry`=23592 AND `Item`=33071;
UPDATE `creature_loot_template` SET `Chance`=40 WHERE `Entry`=23593 AND `Item`=33071;
UPDATE `creature_loot_template` SET `Chance`=39 WHERE `Entry`=23714 AND `Item`=33071;

-- Salvaged Wood (Quest: Sacred Fire (Id: 5062))
DELETE FROM `creature_loot_template` WHERE `Entry`=18952 AND `Item`=25911;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18952, 25911, 44, 1, 'Bonechewer Scavenger - Salvaged Wood');

-- Salvaged Metal (Quest: Sacred Fire (Id: 5062))
DELETE FROM `creature_loot_template` WHERE `Entry`=18952 AND `Item`=25912;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (18952, 25912, 44, 1, 'Bonechewer Scavenger - Salvaged Metal');

-- Hellfire Spineleaf (Quest: Preparing the Salve (Id: 9345))
DELETE FROM `creature_loot_template` WHERE `Entry`=16879 AND `Item`=23205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16879, 23205, 37, 1, 'Starving Helboar - Hellfire Spineleaf');
DELETE FROM `creature_loot_template` WHERE `Entry`=16972 AND `Item`=23205;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16972, 23205, 36, 1, 'Bonestripper Buzzard - Hellfire Spineleaf');

-- Zeppelin Debris (Quest: In Case of Emergency... (Id: 10161))
DELETE FROM `creature_loot_template` WHERE `Entry`=16863 AND `Item`=28116;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16863, 28116, 45, 1, 'Deranged Helboar - Zeppelin Debris');
DELETE FROM `creature_loot_template` WHERE `Entry`=16879 AND `Item`=28116;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16879, 28116, 46, 1, 'Starving Helboar - Zeppelin Debris');
DELETE FROM `creature_loot_template` WHERE `Entry`=16972 AND `Item`=28116;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (16972, 28116, 44, 1, 'Bonestripper Buzzard - Zeppelin Debris');

-- Feralfen Protection Totem (Quest: Spirits of the Feralfen (Id: 9846))
UPDATE `creature_loot_template` SET `Chance`=25 WHERE `Entry`=18113 AND `Item`=24497;
UPDATE `creature_loot_template` SET `Chance`=50 WHERE `Entry`=18114 AND `Item`=24497;
UPDATE `creature_loot_template` SET `Chance`=35 WHERE `Entry`=20270 AND `Item`=24497;

-- Digested Caracoli (Quest: A Rare Bean (Id: 9800))
DELETE FROM `creature_loot_template` WHERE `Entry`=17131 AND `Item`=24419;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (17131, 24419, 39, 1, 'Talbuk Thorngrazer - Digested Caracoli');

-- Ever-burning Ash (Quest: A Haunted History (Horde) / A Ghost in the Machine (Alliance) (Id: 10624 (Horde), 10642 (Alliance)))
DELETE FROM `creature_loot_template` WHERE `Entry`=21408 AND `Item`=30716;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (21408, 30716, 31, 1, 'Felfire Diemetradon - Ever-burning Ash');
DELETE FROM `creature_loot_template` WHERE `Entry`=21878 AND `Item`=30716;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (21878, 30716, 35, 1, 'Felboar - Ever-burning Ash');

-- Warsong Munitions (Quest: Patience is a Virtue that We Don't Need (11606))
UPDATE `creature_loot_template` SET `Chance`=41 WHERE `Entry`=24566 AND `Item`=34709;
UPDATE `creature_loot_template` SET `Chance`=48 WHERE `Entry`=25294 AND `Item`=34709;
UPDATE `creature_loot_template` SET `Chance`=49 WHERE `Entry`=25445 AND `Item`=34709;

-- Super Strong Metal Plate (Quest: Super Strong Metal Plates! (11644))
UPDATE `creature_loot_template` SET `Chance`=47 WHERE `Entry`=25496 AND `Item`=34786;
DELETE FROM `creature_loot_template` WHERE `Entry`=25479 AND `Item`=34786;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (25479, 34786, 42, 1, 'Kvaldir Mistweaver - Super Strong Metal Plate');
