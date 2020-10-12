## Libraries

### GLM
Library for vector matrix calculations.
```
git clone https://github.com/g-truc/glm.git
```

### GLAD
```
git clone https://github.com/Dav1dde/glad.git
```

### GLFW
```
git clone https://github.com/glfw/glfw.git
```

## Questions?

1) Why is the drawing relative to the camera and a scene and all objects needs to be redrawn to simulate that the camera is moving? Cant we just move the camera? Seems like a less expensive calculation to make than redraw all objects and recalculate all their positions. Maybe Im missing something here! How is it solved in multiplayer games?
**Answers**: 
https://stackoverflow.com/questions/9893712/it-is-possible-to-only-move-camera-in-opengl-without-redrawing-the-scene
https://gamedev.stackexchange.com/questions/40741/why-do-we-move-the-world-instead-of-the-camera
