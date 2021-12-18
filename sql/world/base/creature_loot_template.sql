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

-- Cactus Apple (Quest: Galgar's Cactus Apple Surprise (Id: 4402))
-- Mottled Boar (Id: 3098)
DELETE FROM `creature_loot_template` WHERE `Entry` = 3098 AND `Item` = 11583;
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `Chance`, `QuestRequired`, `Comment`) VALUES (3098, 11583, 32, 1, 'Mottled Boar - Cactus Apple');
