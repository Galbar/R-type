return {
  version = "1.1",
  luaversion = "5.1",
  tiledversion = "0.12.3",
  orientation = "orthogonal",
  width = 13,
  height = 9,
  tilewidth = 80,
  tileheight = 80,
  nextobjectid = 3,
  properties = {},
  tilesets = {},
  layers = {
    {
      type = "imagelayer",
      name = "Image Layer 1",
      x = 0,
      y = 0,
      visible = true,
      opacity = 1,
      image = "../textures/credits.jpg",
      properties = {}
    },
    {
      type = "objectgroup",
      name = "Object Layer 1",
      visible = true,
      opacity = 1,
      properties = {},
      objects = {
        {
          id = 1,
          name = "",
          type = "ChangeLevelButton",
          shape = "rectangle",
          x = 721,
          y = 625,
          width = 289,
          height = 93,
          rotation = 0,
          visible = true,
          properties = {
            ["target"] = "main-menu"
          }
        }
      }
    }
  }
}
