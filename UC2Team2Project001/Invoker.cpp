#include "pch.h"
#include "Invoker.h"
#include "CommandTypes.h"

shared_ptr<Invoker> GInvoker = make_shared<Invoker>();

void Invoker::ExecuteCommand(std::shared_ptr<ICommand> _command)
{
    _command->Execute();               // 명령 실행
    undoStack.push(_command);          // Undo 스택에 추가
    while (!redoStack.empty())        // Redo 스택 초기화
    {      
        redoStack.pop();
    }
}

void Invoker::Undo()
{
    if (!undoStack.empty()) 
    {
        auto command = undoStack.top();
        undoStack.pop();
        command->Undo();              // Undo 실행
        redoStack.push(command);      // Redo 스택에 추가
    }
    else 
    {
        std::cout << "No commands to undo.\n";
    }
}

void Invoker::Redo()
{
    if (!redoStack.empty()) 
    {
        auto command = redoStack.top();
        redoStack.pop();
        command->Execute();           // Redo 실행
        undoStack.push(command);      // Undo 스택에 다시 추가
    }
    else 
    {
        // 되돌릴 커멘드가 없습니다.
    }
}
