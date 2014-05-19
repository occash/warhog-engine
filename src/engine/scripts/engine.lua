package.path=package.path..';C:/projects/ModernGL/ModernGL/?.lua;'
local Engine = {}

class 'Component' (BaseComponent)

function Component:__init()
    BaseComponent.__init(self)
end

return { Component = Component }