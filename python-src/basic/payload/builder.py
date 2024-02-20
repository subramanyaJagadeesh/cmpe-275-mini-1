
class BasicBuilder(object):
    def __init__(self):
        pass
        
    def encode(self, name, group, msg):
        # TODO encode message
        payload = (f"{group},{name},{msg}")
        return (f"{len(payload):04d},{payload}")

    def decode(self, raw):
        # TODO complete parsing
        parts = raw.split(",", 4)
        if (len(parts)==4):
            #number,group, name, app
            #number is not accounted in return statement
            return parts[2],parts[1],parts[3]
        elif (len(parts)==3):
            #case for java client that does not have number as part of message
            #group, name, app
            return parts[1],parts[0],parts[2]
        else:
            raise ValueError(f"message format error: {raw}")
