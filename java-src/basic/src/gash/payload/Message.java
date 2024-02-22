package gash.payload;

public class Message {
	private String name, group, text;

	public Message(String name, String group, String text) {
		this.name = name;
		this.group = group;
		this.text = text;
	}

	public Message(String text){
		this.text = text;
	}

	public Message(String group, String text){
		this.group = group;
		this.text = text;
	}

	@Override
	public String toString() {
		var sb = new StringBuilder();
		if(name !=null && name.length() !=0)
			sb.append("from ").append(name);
		if(group != null && group.length() !=0)
			sb.append(", to group: ").append(group);
		if(text != null && text.length() !=0)
			sb.append(", text: ").append(text);

		return sb.toString();
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getGroup() {
		return group;
	}

	public void setGroup(String group) {
		this.group = group;
	}

	public String getText() {
		return text;
	}

	public void setText(String text) {
		this.text = text;
	}
}
