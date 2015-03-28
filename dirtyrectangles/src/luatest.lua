print("Hello World")
my_function(1,2,3,34)
set_callback(function() print("### 1 I am a callCallback") end)
set_callback(function() print("### 2 I am a callCallback") end)
call_callback()
set_callback(function() print("### 3 I am a callCallback") end)
call_callback()
print("EOF")

-- EOF --
