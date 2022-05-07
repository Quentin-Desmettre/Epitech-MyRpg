/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc_texts
*/

#ifndef NPC_TEXTS_H_
    #define NPC_TEXTS_H_
    #include "player.h"

__attribute__((unused)) static const sfIntRect *pl_rects[5] = {
    pl_rect_top, pl_rect_down, pl_rect_left, pl_rect_right, pl_rect_idle
};

__attribute__((unused)) static const char *quest_canceled = "That's okay, no "
"problem. I guess I'll just wait for some PartyGoers to end my life.";

__attribute__((unused)) static const char *quest_accepted = "Thank you so much"
" for accepting my quest.";

__attribute__((unused)) static const char *quest_query = "Will you accept my "
"request ?";

__attribute__((unused)) static const char *quests_texts[3] = {
    "Here, down in the backrooms, there are a lot of ennemies. Partygoers "
    "especially freaks me out, I can't sleep at night because of them. "
    "I would really like them to completely disappear out of this world. "
    "Actually, I would love YOU to kill them for me.",

    "I think you noticed that down here, there is not a lot of water. "
    "I think you noticed that sometimes, you find some almond water on the "
    "floor. But you surely also noticed that you feel more and more thirsty "
    "as time goes by. Please do me a favour, take some of this almond water "
    "you find on the floor and put it into your inventory (using E), and drink"
    " it to stay alive. Doing so shall give you some XP, so you can better "
    "fight partygoers.",

    "Hi partner =) You've been here for a while, haven't you ? You are surely"
    " feeling kind of sad, and exhausted at the moment. Luckily for you, you ca"
    "n have some rest! Down here, there sometimes spawns some magic pills, that"
    " can take you from the baddest mood to the brightest smile! Mens sana in "
    "corpore sano =)) Please take 10 of this pills, so you can escape "
    "from this place safely."
};

__attribute__((unused)) static const char *no_quests = "Hi, you =) I was "
"about to give you a quest, "
"but it looks like you can't carry anymore of them. Before coming back to me, "
"pay your debts and complete some of the quests my friends gave you.";

__attribute__((unused)) static const char *npc_texts[NB_TEXTS] = {
    "Beware of party goers...",
    "You should run away from here.",
    "Don't stay too long in this place, or you will never come back =)",
    "You should try to kiss a party goer ! It's fun =)",
    "Why didn't you invite me to your party?"
};

#endif /* !NPC_TEXTS_H_ */
