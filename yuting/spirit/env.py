# Please install OpenAI SDK first: `pip3 install openai`
import os
from openai import OpenAI


api_key=os.environ.get('DEEPSEEK_API_KEY')
print(api_key)

