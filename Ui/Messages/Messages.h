#ifndef MESSAGES_H
#define MESSAGES_H
#include "../../Types/Types.h"

struct Message {
    std::string text;
    Color color;
    unsigned short duration;
    void* font;
};

class MessageManager{
public:
    MessageManager(Vector2D topLeftPos);
    void Update();
    void AddMessage(Message msg );
    ~MessageManager();
private:
    Vector2D startPos;
    std::vector<Message>* messages;
};

#endif