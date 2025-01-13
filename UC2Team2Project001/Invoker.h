#pragma once
#include <stack>
#include <memory>
class ICommand;

class Invoker 
{
public:
    // 명령 실행
    void ExecuteCommand(std::shared_ptr<ICommand> command);

    void Undo();

    // Redo 실행
    void Redo();

private:
    std::stack<std::shared_ptr<ICommand>> undoStack; // Undo 기록
    std::stack<std::shared_ptr<ICommand>> redoStack; // Redo 기록
};

extern shared_ptr<Invoker> GInvoker;