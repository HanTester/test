import sys, os

PROJECTS_DIR = "/Users/colin/Work/"
SHADER_DIR = PROJECTS_DIR + "Cathode/"

def encrypt(source_file, target_file):
    
    encryptor = PROJECTS_DIR + "EncryptFile/build/Release/EncryptFile"
    
    command = "%s %s %s %s" % (encryptor, source_file, target_file, "Interlace")
    
    exit_code = os.system(command)
    
    if exit_code:
        print "Encrypting file %s: ERROR %d" % (source_file, exit_code)
        sys.exit(2)

if __name__ == "__main__":
    
    TARGET_DIR = sys.argv[1]
    
    print "Building Cathode shaders"
    print "Target: ", TARGET_DIR
    
    include_names = ["Geometry", "Environment", "Picture", "Signals"]
    shader_names = ["Console", "FrameCommon", "FrameBackground", "FramePicture", "ScreenCommon", "ScreenBackground", "ScreenPicture"]
    
    for name in include_names:
        
        encrypt(SHADER_DIR + name + ".glsl", SHADER_DIR + name + ".glsldata")
        os.system("cp %s %s" % (SHADER_DIR + name + ".glsldata", TARGET_DIR + name + ".glsldata"))
        os.system("rm " + SHADER_DIR + name + ".glsldata")
    
    for name in shader_names:
        
        encrypt(SHADER_DIR + name + ".vert", SHADER_DIR + name + ".vertdata")
        os.system("cp %s %s" % (SHADER_DIR + name + ".vertdata", TARGET_DIR + name + ".vertdata"))
        os.system("rm " + SHADER_DIR + name + ".vertdata")
        
        encrypt(SHADER_DIR + name + ".frag", SHADER_DIR + name + ".fragdata")
        os.system("cp %s %s" % (SHADER_DIR + name + ".fragdata", TARGET_DIR + name + ".fragdata"))
        os.system("rm " + SHADER_DIR + name + ".fragdata")
