-- Drop Off Captured Crusader (Quest: Into The Wild Green Yonder (Id: 13045))
DELETE FROM `spell_script_names` WHERE `spell_id`=56684;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (56684, 'spell_drop_off_captured_crusader');

-- Plant Kil'sorrow Banner (Quest: Returning the Favor (Id: 9931))
DELETE FROM `spell_script_names` WHERE `spell_id`=32314;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (32314, 'spell_item_kilsorrow_banner');
