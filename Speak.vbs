Dim userInput
userInput = InputBox("在下面输出你想让电脑说的话!")
Set Sapi = Wscript.CreateObject("SAPI.SpVoice")
Sapi.speak userInput