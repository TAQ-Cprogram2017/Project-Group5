Dim userInput
userInput = InputBox("��������������õ���˵�Ļ�!")
Set Sapi = Wscript.CreateObject("SAPI.SpVoice")
Sapi.speak userInput