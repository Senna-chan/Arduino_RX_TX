Import("env")


# if env.IsIntegrationDump():
#    # stop the current script execution
#    Return()

cxx = env["CXXFLAGS"]

cxx = [x for x in cxx if not "-std" in x]
cxx += ["-std=c++23"]
env.Replace(CXXFLAGS=cxx)
print(cxx)