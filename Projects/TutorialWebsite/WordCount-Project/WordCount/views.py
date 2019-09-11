from django.http import HttpResponse
from django.shortcuts import render
import operator

def homepage(request):
    return render(request, 'home.html')

def count(request):
    fulltext = request.GET['fulltext']
    textCount = len(fulltext.split())

    wordDictionary = {}

    for word in fulltext.split():
        if word in wordDictionary:
            wordDictionary[word] += 1
        else:
            wordDictionary[word] = 1

    sortedWords = sorted(wordDictionary.items(), key=operator.itemgetter(1), reverse=True)

    return render(request, 'count.html',
        {
        'fulltext':fulltext,
        'textCount': textCount,
        'sortedWords': sortedWords
        })

def about(request):
    return render(request, 'about.html')
