import numpy as np
from PIL import Image

def generate_brick_texture():
    # Create a 64x64 texture
    texture = np.zeros((64, 64, 3), dtype=np.uint8)
    
    # Base color (brick red)
    texture[:, :] = [150, 50, 50]
    
    # Add mortar lines
    for i in range(0, 64, 8):
        texture[i:i+2, :] = [100, 100, 100]  # Horizontal mortar
        texture[:, i:i+2] = [100, 100, 100]  # Vertical mortar
    
    return Image.fromarray(texture)

def generate_metal_texture():
    # Create a 64x64 texture
    texture = np.zeros((64, 64, 3), dtype=np.uint8)
    
    # Base color (metal gray)
    texture[:, :] = [100, 100, 100]
    
    # Add some noise for texture
    noise = np.random.randint(-20, 20, (64, 64, 3))
    texture = np.clip(texture + noise, 0, 255)
    
    return Image.fromarray(texture)

def generate_stone_texture():
    # Create a 64x64 texture
    texture = np.zeros((64, 64, 3), dtype=np.uint8)
    
    # Base color (stone gray)
    texture[:, :] = [120, 120, 120]
    
    # Add some noise and patterns
    for i in range(64):
        for j in range(64):
            if (i + j) % 8 < 4:
                texture[i, j] += np.random.randint(-30, 30, 3)
    
    return Image.fromarray(texture)

# Generate and save textures
brick = generate_brick_texture()
metal = generate_metal_texture()
stone = generate_stone_texture()

brick.save("assets/textures/brick.png")
metal.save("assets/textures/metal.png")
stone.save("assets/textures/stone.png") 