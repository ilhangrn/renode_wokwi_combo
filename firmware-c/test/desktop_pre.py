from os.path import join

Import("env")

# When running in the native environment we only want the sum library, not the
# Arduino main application, so exclude the firmware entry point.
env.Append(CPPPATH=[join("$PROJECT_DIR", "src")])
for node in env.GetProjectSources():
    if str(node).endswith(join("src", "main.cpp")):
        env.Ignore(node)
