with open("opening", "rb") as src, open("initial_memdump", "ab") as dest:
    dest.write(src.read())

with open("initial_middle", "rb") as src, open("initial_memdump", "ab") as dest:
    dest.write(src.read())

with open("closing", "rb") as src, open("initial_memdump", "ab") as dest:
    dest.write(src.read())

with open("opening", "rb") as src, open("malicious_memdump", "ab") as dest:
    dest.write(src.read())

with open("malicious_middle", "rb") as src, open("malicious_memdump", "ab") as dest:
    dest.write(src.read())

with open("closing", "rb") as src, open("malicious_memdump", "ab") as dest:
    dest.write(src.read())
