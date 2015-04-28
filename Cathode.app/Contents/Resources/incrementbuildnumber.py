from AppKit import NSMutableDictionary
import os

#configuration = os.environ['CONFIGURATION']

# Get the name of the info.plist file.
infoplist_file = os.environ['INFOPLIST_FILE']

# Load it into a mutable dictionary and update it.
info_dictionary = NSMutableDictionary.dictionaryWithContentsOfFile_(infoplist_file)
bundle_version = int(info_dictionary['CFBundleVersion']) + 1
version_string = str(bundle_version)
info_dictionary['CFBundleVersion'] = version_string

# Write back the updated file.
info_dictionary.writeToFile_atomically_(infoplist_file, True)
