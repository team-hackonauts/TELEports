ALTER TABLE `avatarmap` RENAME TO `chatlist_map`;
ALTER TABLE `chatlist_map` ADD unread_messages INTEGER;
